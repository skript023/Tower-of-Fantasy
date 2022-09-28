#pragma once

namespace big
{
	class teleport_menu
	{
	public:
		static void render_menu();
	private:
		inline static int selected_teleport{ 0 };
		inline static const char* const target[]{ "Supply Pods", "Burried Supply Pods", "Nucleus", "Fire Link", "Flower Throw", "Chest Box", "Dandelion"};
		inline static int selected_method{ 0 };
		inline static const char* const method[]{ "Teleport Standard", "Teleport With Loading" };
		inline static const char* const food[]{"rabit", "fish", "stork", "bug", "Fish"};
	};
}