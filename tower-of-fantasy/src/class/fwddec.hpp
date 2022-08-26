#pragma once

namespace big
{
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
		
		inline bool valid(int i)
		{
			uintptr_t result{};
			if (!ReadProcessMemory(GetCurrentProcess(), this->items[i], &result, sizeof(this->items[i]), nullptr))
			{
				return false;
			}
			return true;
		}

		inline bool valid_ex(int i)
		{
			if (!**items[i])
				return false;

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

	class GWorld;
	class OwningGameInstance;
	class LocalPlayer;
	class Player;
	class PlayerController;
	class Pawn;
	class CharacterMovement;
	class AttributeSet;
	class SkillComponent;

	class Navigation;
	class FNamePool;

	class ULevel;
}