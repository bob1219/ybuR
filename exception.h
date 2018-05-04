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

#ifndef EXCEPTION_H
#define EXCEPTION_H

// standard library
#include <string>

namespace ybur
{
	class exception
	{
	private:
		std::wstring _message;

	public:
		exception() = delete;
		exception(const std::wstring& _message_) : _message{_message_} {}
		exception(const exception&) = default;
		exception(exception&&) = default;

		exception& operator=(const exception&) = default;
		exception& operator=(exception&&) = default;

		const auto message() { return _message; }
	};
}

#endif
