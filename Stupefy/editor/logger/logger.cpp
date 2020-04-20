/****************************************************************************/
/*  logger.cpp                                                              */
/****************************************************************************/
/*                          This file is a part of:                         */
/*                              STUPEFY ENGINE                              */
/*                                                                          */
/****************************************************************************/
/*  Copyright[2020] Harshit Bargujar                                        */
/*                                                                          */
/*  Licensed under the Apache License, Version 2.0 (the "License");         */
/*  you may not use this file except in compliance with the License.        */
/*  You may obtain a copy of the License at                                 */
/*                                                                          */
/*  http://www.apache.org/licenses/LICENSE-2.0                              */
/*                                                                          */
/*  Unless required by applicable law or agreed to in writing, software     */
/*  distributed under the License is distributed on an "AS IS" BASIS,       */
/*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.*/
/*  See the License for the specific language governing permissions and     */
/*  limitations under the License.                                          */
/****************************************************************************/


#include "editor/logger/logger.h"
#include "editor/logger/colorboy.h"

namespace Stupefy
{
	const std::string currenttime(std::string s)
	{
		time_t now = time(0);
		tm* ltm = localtime(&now);
		struct tm tstruct;
		char buf[80];
		tstruct = *localtime(&now);
		if (s == "now")
		{
			strftime(buf, sizeof(buf), "[%Y-%m-%d][%X] ", &tstruct);
		}
		else if (s == "date")
		{
			strftime(buf, sizeof(buf), "[%Y-%m-%d] ", &tstruct);
		}
		return std::string(buf);
	}

	/*inline void fileWriter()
	{
		std::string filepath = "C:\\Users\\HARSHB\\Documents\\Stupefy Log\\Log_" + currenttime("date") + ".txt";
		std::string now = currenttime("now");
		std::ofstream ofs(filepath.c_str(), std::ios_base::out | std::ios_base::app);
		ofs << now << "\t";
		ofs.close();
	}*/

	static void writeLog(const char* prepend, const char* message, va_list args)
	{
		std::cout << currenttime("now");
		vprintf((std::string(prepend) + message + "\n").c_str(), args);

		std::string filepath = "..\\Logs\\Log--" + currenttime("date") + ".txt";
		std::string now = currenttime("now");
		std::ofstream ofs(filepath.c_str(), std::ios_base::out | std::ios_base::app);
		
		ofs << now << "\t" << (std::string(prepend)) << message <<"\n";
		ofs.close();
	}

	void Stupefy::Logger::Trace(const char* message, ...)
	{
		ColorBoy::setupConsole();
		ColorBoy::setTextColor(ColorBoy::WHITE_TXT);
		va_list args;
		va_start(args, message);
		writeLog("[TRACE]: ", message, args);
		va_end(args);
		ColorBoy::restoreConsole();
	}

	void Stupefy::Logger::Log(const char* message, ...)
	{
		ColorBoy::setupConsole();
		ColorBoy::setTextColor(ColorBoy::GREEN_TXT);
		va_list args;
		va_start(args, message);
		writeLog("[LOG]: ", message, args);
		va_end(args);
		ColorBoy::restoreConsole();
	}

	void Stupefy::Logger::Warn(const char* message, ...)
	{
		ColorBoy::setupConsole();
		ColorBoy::setColorAndStyle(ColorBoy::YELLOW_TXT, ColorBoy::BOLD);
		va_list args;
		va_start(args, message);
		writeLog("[WARN]: ", message, args);
		va_end(args);
		ColorBoy::restoreConsole();
	}

	void Stupefy::Logger::Error(const char* message, ...)
	{
		ColorBoy::setupConsole();
		//ColorBoy::setTextColor(RED_TXT);
		//ColorBoy::setStyle(BOLD);
		ColorBoy::setColorAndStyle(ColorBoy::RED_TXT, ColorBoy::BOLD);
		va_list args;
		va_start(args, message);
		writeLog("[ERROR]: ", message, args);
		va_end(args);
		ColorBoy::restoreConsole();
	}

	void Stupefy::Logger::Fatal(const char* message, ...)
	{
		ColorBoy::setupConsole();
		ColorBoy::setBackgroundColor(ColorBoy::RED_BKG);
		ColorBoy::setTextColor(ColorBoy::WHITE_TXT);
		va_list args;
		va_start(args, message);
		writeLog("[FATAL]: ", message, args);
		va_end(args);
		ColorBoy::restoreConsole();

		ASSERT(false);
	}
}