#pragma once

namespace big
{
	struct FPointer
	{
		uintptr_t Dummy;
	};

	struct FQWord
	{
		int A;
		int B;
	};

	template<typename KeyType, typename ValueType>
	class TPair
	{
	public:
		KeyType   Key;
		ValueType Value;
	};

	template<typename T> class TIterator
	{
	public:
		TIterator(T* ptr = nullptr) { m_ptr = ptr; }
		bool operator==(const TIterator<T>& other) const { return (m_ptr == other.m_ptr); }
		bool operator!=(const TIterator<T>& other) const { return (m_ptr != other.m_ptr); }
		TIterator<T>& operator++() { ++m_ptr; return (*this); }
		T& operator*() { return *m_ptr; }
		const T& operator*() const { return *m_ptr; }
		T* operator->() { return m_ptr; }
	protected:
		T* m_ptr;
	};

	/**
	* \brief This is a dummy constructor that does nothing. The purpose of this
	* is so you can create a global TArray in the data segment that gets
	* used by code before startup without worrying about the constructor
	* resetting it after it's already been used. You MUST NOT use it for
	* heap- or stack-allocated TArrays.
	*/
	template <class T, class TT = T>
	class TArray
	{
	public:
		typedef TIterator<T>                       iterator;
		typedef TIterator<const T>                 const_iterator;

		iterator begin()
		{
			return &m_data[0];
		}
		const_iterator begin() const
		{
			return &m_data[0];
		}
		const_iterator cbegin() const
		{
			return &m_data[0];
		}

		iterator end()
		{
			return &m_data[m_count];
		}
		const_iterator end() const
		{
			return &m_data[m_count];
		}
		const_iterator cend() const
		{
			return &m_data[m_count];
		}

		enum ENoInit
		{
			NoInit
		};

		TArray(ENoInit dummy)
		{
		}

		TArray()
		{
			m_max = 0;
			m_count = 0;
			m_data = NULL;
		}

		TArray(int max)
		{
			m_max = max;
			m_count = 0;
			m_data = (T*)malloc(sizeof(T) * max);
		}

		TArray(const TArray<T, TT>& other)
		{
			DoCopy(other);
		}

		TArray(TArray<T, TT>&& other)
		{
			m_data = other.m_data; other.m_data = NULL;
			m_max = other.m_max; other.m_max = 0;
			m_count = other.m_count; other.m_count = 0;
		}

		TArray<T, TT>& operator= (const TArray<T, TT>& other)
		{
			if (&other != this)
			{
				if (m_data != NULL)
				{
					if (m_count > 0)
					{
						DoDelete(0, m_count - 1);
					}
					free(m_data);
				}
				DoCopy(other);
			}
			return *this;
		}

		TArray<T, TT>& operator= (TArray<T, TT>&& other)
		{
			if (m_data)
			{
				if (m_count > 0)
				{
					DoDelete(0, m_count - 1);
				}
				free(m_data);
			}
			m_data = other.m_data; other.m_data = NULL;
			m_max = other.m_max; other.m_max = 0;
			m_count = other.m_count; other.m_count = 0;
			return *this;
		}

		~TArray()
		{
			if (m_data)
			{
				if (m_count > 0)
				{
					DoDelete(0, m_count - 1);
				}
				free(m_data);
				m_data = NULL;
				m_count = 0;
				m_max = 0;
			}
		}

		bool operator==(const TArray<T>& other) const
		{
			if (m_count != other.m_count)
			{
				return false;
			}
			for (unsigned int i = 0; i < m_count; ++i)
			{
				if (m_data[i] != other.m_data[i])
				{
					return false;
				}
			}
			return true;
		}
		// Return a reference to an element
		T& operator[] (size_t index) const
		{
			return m_data[index];
		}
		// Returns the value of an element
		TT operator() (size_t index) const
		{
			return m_data[index];
		}
		// Returns a reference to the last element
		T& last() const
		{
			return m_data[m_count - 1];
		}
		
		unsigned int find(const T& item) const
		{
			unsigned int i;
			for (i = 0; i < m_count; ++i)
			{
				if (m_data[i] == item)
					break;
			}
			return i;
		}

		unsigned int push(const T& item)
		{
			grow(1);
			::new((void*)&m_data[m_count]) T(item);
			return m_count++;
		}

		bool pop()
		{
			if (m_count > 0)
			{
				m_data[--m_count].~T();
				return true;
			}
			return false;
		}

		bool pop(T& item)
		{
			if (m_count > 0)
			{
				item = m_data[--m_count];
				m_data[m_count].~T();
				return true;
			}
			return false;
		}

		void remove(unsigned int index)
		{
			if (index < m_count)
			{
				m_data[index].~T();
				if (index < --m_count)
				{
					memmove(&m_data[index], &m_data[index + 1], sizeof(T) * (m_count - index));
				}
			}
		}

		void remove(unsigned int index, int deletecount)
		{
			if (index + deletecount > m_count)
			{
				deletecount = m_count - index;
			}
			if (deletecount > 0)
			{
				for (int i = 0; i < deletecount; i++)
				{
					m_data[index + i].~T();
				}
				m_count -= deletecount;
				if (index < m_count)
				{
					memmove(&m_data[index], &m_data[index + deletecount], sizeof(T) * (m_count - index));
				}
			}
		}

		/**
		 * \Inserts an item into the array, shifting elements as needed
		 * \param insert(unsigned int index, const T& item)
		 */
		void insert(unsigned int index, const T& item)
		{
			if (index >= m_count)
			{
				// Inserting somewhere past the end of the array, so we can
				// just add it without moving things.
				resize(index + 1);
				::new ((void*)&m_data[index]) T(item);
			}
			else
			{
				// Inserting somewhere in the middle of the array,
				// so make room for it
				resize(m_count + 1);

				// Now move items from the index and onward out of the way
				memmove(&m_data[index + 1], &m_data[index], sizeof(T) * (m_count - index - 1));

				// And put the new element in
				::new ((void*)&m_data[index]) T(item);
			}
		}

		void shrink_to_fit()
		{
			if (m_max > m_count)
			{
				m_max = m_count;
				if (m_max == 0)
				{
					if (m_data != NULL)
					{
						free(m_data);
						m_data = NULL;
					}
				}
				else
				{
					DoResize();
				}
			}
		}

		/**
		 * \brief Grow Array to be large enough to hold amount more entries without further growing.
		 * \param grow(unsigned int amount)
		 */
		void grow(unsigned int amount)
		{
			if (m_count + amount > m_max)
			{
				const unsigned int choicea = m_count + amount;
				const unsigned int choiceb = m_max = (m_max >= 16) ? m_max + m_max / 2 : 16;
				m_max = (choicea > choiceb ? choicea : choiceb);
				DoResize();
			}
		}

		/**
		 * \brief Resize Array so that it has exactly amount entries in use.
		 * \param resize(unsigned int amount)
		 */
		void resize(unsigned int amount)
		{
			if (m_count < amount)
			{
				// Adding new entries
				grow(amount - m_count);
				for (unsigned int i = m_count; i < amount; ++i)
				{
					::new((void*)&m_data[i]) T;
				}
			}
			else if (m_count != amount)
			{
				// Deleting old entries
				DoDelete(amount, m_count - 1);
			}
			m_count = amount;
		}

		/**
		 * \brief Reserves amount entries at the end of the array, but does nothing with them.
		 * \param reserve(unsigned int amount)
		 */
		unsigned int reserve(unsigned int amount)
		{
			grow(amount);
			unsigned int place = m_count;
			m_count += amount;
			for (unsigned int i = place; i < m_count; ++i)
			{
				::new((void*)&m_data[i]) T;
			}
			return place;
		}

		unsigned int size() const
		{
			return m_count;
		}

		unsigned int max() const
		{
			return m_max;
		}

		void clear()
		{
			if (m_count > 0)
			{
				DoDelete(0, m_count - 1);
				m_count = 0;
			}
		}

	public:
		T* m_data = nullptr;
		uint32_t m_count = 0;
		uint32_t m_max = 0;
	private:
		void DoCopy(const TArray<T>& other)
		{
			m_max = m_count = other.m_count;
			if (m_count != 0)
			{
				m_data = (T*)malloc(sizeof(T) * m_max);
				for (unsigned int i = 0; i < m_count; ++i)
				{
					::new(&m_data[i]) T(other.m_data[i]);
				}
			}
			else
			{
				m_data = NULL;
			}
		}

		void DoResize()
		{
			size_t allocsize = sizeof(T) * m_max;
			m_data = (T*)realloc(m_data, allocsize);
		}

		void DoDelete(unsigned int first, unsigned int last)
		{
			assert(last != ~0u);
			for (unsigned int i = first; i <= last; ++i)
			{
				m_data[i].~T();
			}
		}
	};

	struct FString : private TArray<wchar_t>
	{
		FString() = default;
		FString(wchar_t* str)
		{
			lstrcpy(m_data, str);
		}

		inline std::wstring get_wstring() { return std::wstring(this->m_data); }

		inline wchar_t* c_str() { return this->m_data; }

		inline std::string to_string() const
		{
			auto length = std::wcslen(this->m_data);

			std::string str(length, '\0');

			std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(this->m_data, this->m_data + length, '?', &str[0]);

			return str;
		}

		inline std::string get_string()
		{

			auto length = this->size();

			std::string str(length, '\0');

			std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(this->m_data, this->m_data + length, '?', &str[0]);

			std::string search = "\x0A";

			for (int i = str.find(search); i >= 0; i = str.find(search))
				str.replace(i, search.size(), " ");

			return str;
		}

		inline const wchar_t* convert(const char* c)
		{
			const size_t cSize = strlen(c) + 1;
			wchar_t* wc = new wchar_t[cSize];
			mbstowcs(wc, c, cSize);

			return wc;
		}
	};

	struct FText
	{
		FString* m_text;
		char m_unknown_data[0x30];

		inline wchar_t* c_str() const
		{
			return m_text->c_str();
		}
	};

	struct EvadeBeanParam
	{
		int m_rand_bean; //0x21D0
		int m_cur_bean_count; //0x21D4
		int64_t m_change_time; //0x21D8
	};

	class GWorld;
	class OwningGameInstance;
	class LocalPlayer;
	class Player;
	class PlayerController;
	class Pawn;
	class CharacterMovement;
	class AttributeSet;
	class SkillComponent;

	class AcknowledgedPawn;
	class QuestComponent;
	class CapsuleComponent;

	class Navigation;
	class FNamePool;

	class ULevel;

	class FUObjectItem;
	class TUObjectArray;
	class FUObjectArray;
	class UObject;

	template<typename ElementType, int32_t MaxTotalElements, int32_t ElementsPerChunk>
	class TStaticIndirectArrayThreadSafeRead;

	class FName;

	class FScriptInterface;
	template<class InterfaceType>
	class TScriptInterface;

	class UFunction;
	class UClass;
}