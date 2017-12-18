/* Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.

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

#include "sql/dd/impl/tables/spatial_reference_systems.h"

#include <string.h>
#include <new>

#include "m_ctype.h"
#include "sql/dd/impl/raw/object_keys.h"                // Parent_id_range_key
#include "sql/dd/impl/raw/raw_record.h"
#include "sql/dd/impl/tables/dd_properties.h"               // TARGET_DD_VERSION
#include "sql/dd/impl/types/object_table_definition_impl.h"
#include "sql/dd/impl/types/spatial_reference_system_impl.h"// dd::Spatial_refere...

namespace dd {
namespace tables {

const Spatial_reference_systems & Spatial_reference_systems::instance()
{
  static Spatial_reference_systems *s_instance=
    new Spatial_reference_systems();
  return *s_instance;
}

///////////////////////////////////////////////////////////////////////////

Spatial_reference_systems::Spatial_reference_systems()
{
  // Note: The maximum length of various strings is hard-coded here. These
  // lengths must match those in sql/sql_cmd_srs.cc.

  m_target_def.set_table_name("st_spatial_reference_systems");

  m_target_def.add_field(FIELD_ID,
                         "FIELD_ID",
                         "id INTEGER UNSIGNED NOT NULL");
  m_target_def.add_field(FIELD_CATALOG_ID, "FIELD_CATALOG_ID",
                         "catalog_id BIGINT UNSIGNED NOT NULL");
  m_target_def.add_field(FIELD_NAME,
                         "FIELD_NAME",
                         "name CHARACTER VARYING(80)\n"
                         "NOT NULL COLLATE utf8_general_ci");
  m_target_def.add_field(FIELD_LAST_ALTERED,
                         "FIELD_LAST_ALTERED",
                         "last_altered TIMESTAMP NOT NULL\n"
                         "DEFAULT CURRENT_TIMESTAMP\n"
                         "ON UPDATE CURRENT_TIMESTAMP");
  m_target_def.add_field(FIELD_CREATED,
                         "FIELD_CREATED",
                         "created TIMESTAMP NOT NULL\n"
                         "DEFAULT CURRENT_TIMESTAMP");
  m_target_def.add_field(FIELD_ORGANIZATION,
                         "FIELD_ORGANIZATION",
                         "organization CHARACTER VARYING(256)\n"
                         "COLLATE utf8_general_ci");
  m_target_def.add_field(FIELD_ORGANIZATION_COORDSYS_ID,
                         "FIELD_ORGANIZATION_COORDSYS_ID",
                         "organization_coordsys_id INTEGER UNSIGNED");
  m_target_def.add_field(FIELD_DEFINITION,
                         "FIELD_DEFINITION",
                         "definition CHARACTER VARYING(4096)\n"
                         "NOT NULL");
  m_target_def.add_field(FIELD_DESCRIPTION,
                         "FIELD_DESCRIPTION",
                         "description CHARACTER VARYING(2048)");
  m_target_def.add_field(FIELD_OPTIONS,
                         "FIELD_OPTIONS",
                         "options MEDIUMTEXT");

  m_target_def.add_index(INDEX_PK_ID,
                         "INDEX_PK_ID",
                         "PRIMARY KEY (id)");
  m_target_def.add_index(INDEX_UK_CATALOG_ID_NAME,
                         "INDEX_UK_CATALOG_ID_NAME",
                         "UNIQUE KEY SRS_NAME (catalog_id, name)");
  m_target_def.add_index(INDEX_UK_CATALOG_ID_ORG_ID,
                         "INDEX_UK_CATALOG_ID_ORG_ID",
                         "UNIQUE KEY ORGANIZATION_AND_ID (catalog_id, "
                         "organization, organization_coordsys_id)");

  m_target_def.add_foreign_key(FK_CATALOG_ID,
                               "FK_CATALOG_ID",
                               "FOREIGN KEY (catalog_id) REFERENCES \
                                  catalogs(id)");

  m_target_def.add_populate_statement(
      "INSERT INTO st_spatial_reference_systems (id, catalog_id, name, "
      "definition) VALUES (0, 1, '', '')");
}


///////////////////////////////////////////////////////////////////////////

Spatial_reference_system*
Spatial_reference_systems::create_entity_object(const Raw_record &) const
{
  return new (std::nothrow) Spatial_reference_system_impl();
}

///////////////////////////////////////////////////////////////////////////

bool Spatial_reference_systems::update_object_key(Item_name_key *key,
                                                  Object_id catalog_id,
                                                  const String_type &name)
{
  // Construct a lowercase version of the key. The collation of the
  // name column is also accent insensitive, but we don't have a
  // function to make a canonical accent insensitive representation
  // yet. We have to settle for a lowercase name here and reject
  // accent variations when trying to store the object.
  char lowercase_name[257];
  memcpy(lowercase_name, name.c_str(), name.size() + 1);
  my_casedn_str(&my_charset_utf8_general_ci, lowercase_name);
  key->update(FIELD_CATALOG_ID, catalog_id, FIELD_NAME, lowercase_name);
  return false;
}

///////////////////////////////////////////////////////////////////////////

/* purecov: begin deadcode */
Object_key *
Spatial_reference_systems::create_key_by_catalog_id(Object_id catalog_id)
{
  return new (std::nothrow) Parent_id_range_key(
          INDEX_UK_CATALOG_ID_NAME, FIELD_CATALOG_ID, catalog_id);
}
/* purecov: end */

///////////////////////////////////////////////////////////////////////////

}
}