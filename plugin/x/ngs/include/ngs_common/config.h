/*
 * Copyright (c) 2017, 2018, Oracle and/or its affiliates. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2.0,
 * as published by the Free Software Foundation.
 *
 * This program is also distributed with certain software (including
 * but not limited to OpenSSL) that is licensed under separate terms,
 * as designated in a particular file or component or in included license
 * documentation.  The authors of MySQL hereby grant you an additional
 * permission to link the program and your derivative works with the
 * separately licensed software that they have included with MySQL.
 *  
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License, version 2.0, for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA
 */

#ifndef MYSQLX_XPL_CONFIG_H
#define MYSQLX_XPL_CONFIG_H


#ifdef HAVE_WOLFSSL
#define IS_WOLFSSL_OR_OPENSSL(Y, O) Y
#else // HAVE_WOLFSSL
#define IS_WOLFSSL_OR_OPENSSL(Y, O) O
#endif // HAVE_WOLFSSL

#if defined(HAVE_SYS_UN_H)
#define HAVE_UNIX_SOCKET(YES,NO) YES
#else
#define HAVE_UNIX_SOCKET(YES,NO) NO
#endif // defined(HAVE_SYS_UN_H)

#endif // MYSQLX_XPL_CONFIG_H