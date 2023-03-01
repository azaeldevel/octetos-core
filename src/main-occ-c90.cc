
/*
 * develop-lexer-c90.cc
 * Copyright (C) 2022 Azael Reyes <azael.devel@gmail.com>
 *
 * Octetos Compuler Collection is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CC is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "C90-v0.hh"

namespace occ_here = oct::cc::v0;
static int counter = 0;

template<typename T>
bool lexing(T& lex)
{
	//core_here::lex::Tokenized<char, occ_here::c90::Tokens> actual;

	//std::string strcat;
	while (lex.next() != occ_here::c90::Tokens::none)
	{
		//strcat.clear ();
		//strcat = occ_here::c90::category(actual.token);
		//if(not strcat.empty()) std::cout << strcat << " " << (std::string)actual << "\n";
		counter++;
	}

	return true;
}


int main(int argc, char* argv[])
{
	//std::filesystem::path file1_c90 = "C:\\Users\\Azael\\Documents\\develop\\octetos\\OCC\\tests\\main-ansi-90.c";
	if(argc < 2) throw oct::core::v3::exception("Agrege archivo fuente.");
	std::filesystem::path file1_c90 = argv[1];
	//const char* str_c90 = "struct auto char break switch volatil void int 923456789 5";
	core_next::Buffer<char> buff1_c90(file1_c90);
	const occ_here::c90::TTB tt_c90;
	//const occ_here::c90::TT tt_c90 = occ_here::c90::create_lexer();
	core_next::lex::Lexer<char, occ_here::c90::Tokens, core_here::lex::State,core_here::lex::TTB<char,occ_here::c90::Tokens, core_here::lex::State,occ_here::c90::amount_states,occ_here::c90::amount_transitions,occ_here::c90::amount_symbols>> lex_c90(tt_c90, buff1_c90);
		
	//std::cout << "Compilation... \n";
	if(lexing(lex_c90))
	{
		//std::cout << "... done\n";
	}
	else
	{
		//std::cout << "... fail\n";
	}
	
	return EXIT_SUCCESS;
}

