/* Copyright (c) 2017 Oracle and/or its affiliates. All rights reserved.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   51 Franklin Street, Suite 500, Boston, MA 02110-1335 USA */

#ifndef DD_TABLES__RESOURCE_GROUPS_INCLUDED
#define DD_TABLES__RESOURCE_GROUPS_INCLUDED

#include <new>
#include <string>

#include "sql/dd/impl/raw/object_keys.h"
#include "sql/dd/impl/types/resource_group_impl.h"
#include "sql/dd/impl/types/entity_object_table_impl.h"   // dd::Object_table_i...
#include "sql/dd/types/resource_group.h"

namespace dd
{

class Raw_record;

namespace tables
{
class Resource_groups : virtual public Entity_object_table_impl
{
public:
  Resource_groups();

  static const Resource_groups &instance();

  enum enum_fields
  {
    FIELD_ID,
    FIELD_RESOURCE_GROUP_NAME,
    FIELD_RESOURCE_GROUP_TYPE,
    FIELD_RESOURCE_GROUP_ENABLED,
    FIELD_CPU_ID_MASK,
    FIELD_THREAD_PRIORITY,
    FIELD_OPTIONS
  };

  enum enum_indexes
  {
    INDEX_PK_ID= static_cast<uint>(Common_index::PK_ID),
    INDEX_UK_RESOURCE_GROUP_NAME= static_cast<uint>(Common_index::UK_NAME)
  };

  enum enum_foreign_keys
  {
  };

public:
  Resource_group *create_entity_object(const Raw_record &) const override
  { return new (std::nothrow) Resource_group_impl(); }

  static bool update_object_key(Global_name_key *key,
                                const String_type &resource_group_name);
};
} // namespace tables
} // namespace dd


#endif // DD_TABLES__RESOURCE_GROUPS_INCLUDED