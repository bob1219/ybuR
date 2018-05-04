// Copyright 2018 Daiki Yoshida. All rights reserved.
//
// This file is part of ybuR.
//
// ybuR is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// ybuR is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with ybuR. If not, see <https://www.gnu.org/licenses/>.

// standard library
#include <iostream>
#include <clocale>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iterator>
#include <memory>
#include <cstring>
#include <exception>

// boost
#include <boost/format.hpp>
#include <boost/tokenizer.hpp>
#include <boost/system/system_error.hpp>

// header
#include "exception.h"
#include "function.h"

// using
using namespace std;
using namespace boost;

int wmain(int argc, wchar_t** argv)
{
	try
	{
		wcout.imbue(locale{""});
		wcerr.imbue(locale{""});
		wcin.imbue(locale{""});
		setlocale(LC_ALL, "");

		if(argc != 2)
		{
			wcerr << wformat{L"Usage: %1% [filename]"} % argv[0] << endl;
			return EXIT_FAILURE;
		}

		wifstream file;
		file.imbue(locale{""});
		file.open(argv[1]);
		if(file.fail())
			throw ybur::exception{L"failed open file"};

		using wseparator = char_separator<wchar_t, char_traits<wchar_t>>;
		using wtokenizer = tokenizer<wseparator, wstring::const_iterator, wstring>;
		wtokenizer Tokenizer{wstring{istreambuf_iterator<wchar_t>{file}, istreambuf_iterator<wchar_t>{}}, wseparator{"\n"}};
		interpret(vector<wstring>{begin(Tokenizer), end(Tokenizer)});

		return EXIT_SUCCESS;
	}
	catch(boost::system::system_error& e)
	{
		const auto		mess_c{e.what()};
		const auto		mess_size{strlen(mess_c) + 1};
		unique_ptr<wchar_t[]>	mess{new wchar_t[mess_len]};
		mbstowcs(mess.get(), mess_c, mess_len);

		wcerr << L"error:" << endl;
		wcerr << mess.get() << endl;
		wcerr << wformat{L"(error code: %1%)"} % e.code().value() << endl;
	}
	catch(std::exception& e)
	{
		const auto		mess_c{e.what()};
		const auto		mess_size{strlen(mess_c) + 1};
		unique_ptr<wchar_t[]>	mess{new wchar_t[mess_len]};
		mbstowcs(mess.get(), mess_c, mess_len);

		wcerr << L"error:" << endl;
		wcerr << mess.get() << endl;
	}
	catch(ybur::exception& e)
	{
		wcerr << L"error:" << endl;
		wcerr << e.message() << endl;
	}

	return EXIT_FAILURE;
}
