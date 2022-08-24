#pragma once
#include "common.hpp"

namespace big
{
	template <typename TP>
	std::time_t to_time_t(TP tp)
	{
		using namespace std::chrono;
		auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
			+ system_clock::now());
		return system_clock::to_time_t(sctp);
	}

	enum class log_color : std::uint16_t {
		red = FOREGROUND_RED,
		green = FOREGROUND_GREEN,
		blue = FOREGROUND_BLUE,
		intensify = FOREGROUND_INTENSITY
	};

	inline log_color operator|(log_color a, log_color b)
	{
		return static_cast<log_color>(static_cast<std::underlying_type_t<log_color>>(a) | static_cast<std::underlying_type_t<log_color>>(b));
	}

	class logger;
	inline logger* g_logger{};

	class logger {
	public:
		explicit logger() :
			m_file_path(std::getenv("appdata"))
		{
			if ((m_did_console_exist = AttachConsole(GetCurrentProcessId())) == false)
				AllocConsole();

			if ((m_console_handle = GetStdHandle(STD_OUTPUT_HANDLE)) != nullptr)
			{
				SetConsoleTitleA("Tower of Fantasy");
				SetConsoleOutputCP(CP_UTF8);

				m_console_out.open("CONOUT$", std::ios_base::out | std::ios_base::app);
			}

			m_file_path /= "Tower of Fantasy";
			std::filesystem::path m_backup_path = m_file_path;
			m_backup_path /= "Backup";
			try
			{
				if (!std::filesystem::exists(m_file_path))
				{
					std::filesystem::create_directory(m_file_path);
				}
				else if (!std::filesystem::is_directory(m_file_path))
				{
					std::filesystem::remove(m_file_path);
					std::filesystem::create_directory(m_file_path);
				}
				if (!std::filesystem::exists(m_backup_path))
				{
					std::filesystem::create_directory(m_backup_path);
				}
				else if (!std::filesystem::is_directory(m_backup_path))
				{
					std::filesystem::remove(m_backup_path);
					std::filesystem::create_directory(m_backup_path);
				}

				m_file_path /= "Tower of Fantasy.log";

				if (std::filesystem::exists(m_file_path))
				{
					auto file_time = std::filesystem::last_write_time(m_file_path);
					auto timet = to_time_t(file_time);
					auto local_time = std::localtime(&timet);

					auto bigbase_timestamp = std::format("{:0>2}-{:0>2}-{}-{:0>2}-{:0>2}-{:0>2} Tower of Fantasy.log", local_time->tm_mon + 1, local_time->tm_mday, local_time->tm_year + 1900, local_time->tm_hour, local_time->tm_min, local_time->tm_sec);

					std::filesystem::copy_file(m_file_path, m_backup_path / bigbase_timestamp);
				}

				m_file_out.open(m_file_path, std::ios_base::out | std::ios_base::trunc);
			}
			catch (std::filesystem::filesystem_error const& error)
			{
				m_console_out << error.what();
			}

			g_logger = this;
		}

		~logger()
		{
			if (!m_did_console_exist)
				FreeConsole();

			g_logger = nullptr;
		}

		void log_raw(log_color color, const char* format)
		{
			raw_to_console(color, format);
		}

		void log(log_color color, std::string_view prefix, const char* format, va_list args)
		{
			auto time_since_epoch = std::time(nullptr);
			auto local_time = std::localtime(&time_since_epoch);

			auto console_timestamp = std::format("[{:0>2}:{:0>2}:{:0>2}]", local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
			auto file_timestamp = std::format("[{}-{}-{} {:0>2}:{:0>2}:{:0>2}]", local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday, local_time->tm_hour, local_time->tm_min, local_time->tm_sec);

			std::size_t length = std::vsnprintf(nullptr, 0, format, args) + 1;
			auto message = std::make_unique<char[]>(length);

			std::uninitialized_fill_n(message.get(), length, '\0');
			std::vsnprintf(message.get(), length, format, args);

			raw_to_console(color, console_timestamp, " [", prefix, "] ", message.get(), "\n");
			raw_to_file(file_timestamp, " [", prefix, "] ", message.get(), "\n");
		}

		void log_file(std::string_view prefix, const char* format, va_list args)
		{
			auto time_since_epoch = std::time(nullptr);
			auto local_time = std::localtime(&time_since_epoch);

			auto console_timestamp = std::format("[{:0>2}:{:0>2}:{:0>2}]", local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
			auto file_timestamp = std::format("[{}-{}-{} {:0>2}:{:0>2}:{:0>2}]", local_time->tm_year + 1900, local_time->tm_mon + 1, local_time->tm_mday, local_time->tm_hour, local_time->tm_min, local_time->tm_sec);

			std::size_t length = std::vsnprintf(nullptr, 0, format, args) + 1;
			auto message = std::make_unique<char[]>(length);

			std::uninitialized_fill_n(message.get(), length, '\0');
			std::vsnprintf(message.get(), length, format, args);

			raw_to_file(file_timestamp, " [", prefix, "] ", message.get(), "\n");
		}

		inline void file(const char* format, ...)
		{
			if (g_logger)
			{
				va_list args{};
				va_start(args, format);
				this->log_file("FILE", format, args);
				va_end(args);
			}
			else
			{
				DebugBreak();
			}
		}

		inline void info(const char* format, ...)
		{
			if (g_logger)
			{
				va_list args{};
				va_start(args, format);
				this->log(log_color::green | log_color::intensify, "INFO", format, args);
				va_end(args);
			}
			else
			{
				DebugBreak();
			}
		}

		inline void warning(const char* format, ...)
		{
			if (g_logger)
			{
				va_list args{};
				va_start(args, format);
				this->log(log_color::red, "WARNING", format, args);
				va_end(args);
			}
			else
			{
				DebugBreak();
			}
		}

		inline void error(const char* format, ...)
		{
			if (g_logger)
			{
				va_list args{};
				va_start(args, format);
				this->log(log_color::red | log_color::intensify, "FATAL", format, args);
				va_end(args);
			}
			else
			{
				DebugBreak();
			}
		}

		inline void trace(const char* format, ...)
		{
			if (g_logger)
			{
				va_list args{};
				va_start(args, format);
				this->log(log_color::green | log_color::intensify, "TRACE", format, args);
				va_end(args);
			}
			else
			{
				DebugBreak();
			}
		}

		inline void raw(const char* format)
		{
			if (g_logger)
			{
				this->log_raw(log_color::green | log_color::intensify, format);
			}
			else
			{
				DebugBreak();
			}
		}
	private:
		template <typename ...Args>
		void raw_to_console(log_color color, Args const &...args)
		{
			if (m_console_handle)
			{
				SetConsoleTextAttribute(m_console_handle, static_cast<std::uint16_t>(color));
			}

			if (m_console_out)
			{
				((m_console_out << args), ...);
				m_console_out << std::flush;
			}
		}

		template <typename ...Args>
		void raw_to_file(Args const &...args)
		{
			if (m_file_out)
			{
				((m_file_out << args), ...);
				m_file_out << std::flush;
			}
		}
	private:
		bool m_did_console_exist{};
		HANDLE m_console_handle{};
		std::ofstream m_console_out;

		std::filesystem::path m_file_path;
		std::ofstream m_file_out;
	};

#define HEX_TO_UPPER(value) "0x" << std::hex << std::uppercase << (DWORD64)value << std::dec << std::nouppercase
}