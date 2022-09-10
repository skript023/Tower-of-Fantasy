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

	template <typename T>
	struct TArray
	{
		inline T& operator[](const int i) { return items[i]; }

		inline const T& operator[](const int i) const { return items[i]; }

		inline static TArray<T> init(const std::vector<T>& items)
		{
			TArray<T> ret;
			ret.item_count = ret.max_item = items.size();
			ret.items = new T[ret.item_count];
			for (int i = 0; i < ret.item_count; i++)
				ret.items[i] = items[i];
			return ret;
		}

		inline void uninit()
		{
			delete[] this->items;
		}

		inline std::vector<T> to_vector()
		{
			std::vector<T> vector;
			for (int i = 0; i < item_count; i++)
			{
				if (!valid(i)) continue;
				vector.push_back(items[i]);
			}

			return vector;
		}

		inline bool valid(int i)
		{
			if (item_count > max_item || !items[i])
				return false;

			return true;
		}

		inline bool valid()
		{
			return item_count < max_item;
		}

		inline bool valid_ex(int i)
		{
			uintptr_t result{};
			if (IsBadReadPtr(this->items[i], sizeof(this->items[i])))
			{
				return false;
			}
			return true;
		}

		inline int count()
		{
			return item_count;
		}

		inline int max_count()
		{
			return max_item;
		}

		T* items = nullptr;
		int item_count = 0;
		int max_item = 0;
	};

	struct FString : public TArray<wchar_t>
	{
		inline wchar_t* get_wstring() { return this->items; }

		inline std::string get_string()
		{

			int size = WideCharToMultiByte(CP_UTF8, 0, items, item_count, nullptr, 0, nullptr, nullptr);
			std::string str(size, 0);
			WideCharToMultiByte(CP_UTF8, 0, items, item_count, &str[0], size, nullptr, nullptr);
			return str;
		}
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