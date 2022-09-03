#include "fname_pool.hpp"
#include "pointers.hpp"

namespace big
{
    std::string FName::get_name() const
    {
        auto entry = g_pointers->m_name->m_entry_allocator.resolve(get_display_index());
        auto name = entry->get_string();
        if (this->m_number > 0)
        {
            name += '_' + std::to_string(this->m_number);
        }
        auto pos = name.rfind('/');
        if (pos == std::string::npos)
        {
            return name;
        }

        return name.substr(pos + 1);
    }

    const FNameEntry* FName::get_display_name_entry() const
    {
        return g_pointers->m_name->m_entry_allocator.resolve(get_display_index());
    }
}