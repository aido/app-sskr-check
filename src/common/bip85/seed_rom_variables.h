/*******************************************************************************
 *   (c) 2016-2022 Ledger SAS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#pragma once

#define BIP85_ENTROPY_LENGTH 64
#define BASE64_TABLE_LENGTH  64
#define BASE64_ENCODE_LENGTH 88
#define BASE85_TABLE_LENGTH  85
#define BASE85_ENCODE_LENGTH 80

extern unsigned char const WIDE BASE64_TABLE[BASE64_TABLE_LENGTH];
extern unsigned char const WIDE BASE85_TABLE[BASE85_TABLE_LENGTH];
