
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
#include <chrono>
#include <algorithm>
#include <iterator>

#include "C90-v0.hh"

namespace occ_here = oct::cc::v0;



int main()
{

	std::cout << "///>>>A section\n\n\n";
	///>>>A
	std::filesystem::path file1_c90 = "C:\\Users\\Azael\\Documents\\develop\\octetos\\OCC\\tests\\main-ansi-90.c";
	//const char* str_c90 = "auto char break switch volatil void int 923456789 5 j a0 aabcd a1_test z juan contianer09 _09cont _09cont % ? #";
	const char* str_c90 = "auto char break switch volatil void int 923456789 5 j a0 aabcd a1_test z juan contianer09 _09cont _09cont % ? #";
	core_next::Buffer<char> buff1_c90(str_c90);
	//constexpr auto tt_c90 = occ_here::c90::create_lexer_a();
	occ_here::c90::TTA tt_c90;
	//std::cout << "TT listing...\n";
	//tt_c90.print(std::cout);
	//tt_c90.check(std::cout);
	std::cout << "\n";
	core_next::lex::Lexer<char, occ_here::c90::Tokens, core_here::lex::State,core_here::lex::TTA<char,occ_here::c90::Tokens, core_here::lex::State>> lex_c90(tt_c90, buff1_c90);

	std::cout << "\n\n";
	occ_here::c90::Tokens tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::keyword_auto)
	{
		std::cout << "Fallo, se espera keyword auto, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "TT size : " << tt_c90.size() << "\n";

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::keyword_char)
	{
		std::cout << "Fallo, se espera keywod char, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::keyword_break)
	{
		std::cout << "Fallo, se espera keywod break, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::keyword_switch)
	{
		std::cout << "Fallo, se espera keywod switch, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::keyword_volatil)
	{
		std::cout << "Fallo, se espera keywod volatil, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::keyword_void)
	{
		std::cout << "Fallo, se espera keywod void, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::keyword_int)
	{
		std::cout << "Fallo, se espera keywod int, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::integer)
	{
		std::cout << "Fallo, se espera integer, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::integer)
	{
		std::cout << "Fallo, se espera integer, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::identifier)
	{
		std::cout << "Fallo, se espera identifier, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::identifier)
	{
		std::cout << "Fallo, se espera identifier, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::identifier)
	{
		std::cout << "Fallo, se espera identifier, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::identifier)
	{
		std::cout << "Fallo, se espera identifier, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::identifier)
	{
		std::cout << "Fallo, se espera identifier, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::identifier)
	{
		std::cout << "Fallo, se espera identifier, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::identifier)
	{
		std::cout << "Fallo, se espera identifier, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::identifier)
	{
		std::cout << "Fallo, se espera identifier, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::identifier)
	{
		std::cout << "Fallo, se espera identifier, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != (occ_here::c90::Tokens)'%')
	{
		std::cout << "Fallo, se espera %, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != (occ_here::c90::Tokens)'?')
	{
		std::cout << "Fallo, se espera %, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != (occ_here::c90::Tokens)'#')
	{
		std::cout << "Fallo, se espera %, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";
    std::cout << "///<<<A section\n\n\n";

	/*auto begin1 = std::chrono::high_resolution_clock::now();
	occ_here::c90::TT tt_c90test[10];
	auto end1 = std::chrono::high_resolution_clock::now();
	auto elapsed1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - begin1);
	std::cout << "Tiempo : " << elapsed1 << "\n";

	auto begin2 = std::chrono::high_resolution_clock::now();
	std::vector<std::vector<core_here::lex::Transition<occ_here::c90::Tokens, core_here::lex::State>>> tts[10];
	for(size_t i = 0; i < 10; i++)
    {
        tts[i].resize(100);
    }
	auto end2 = std::chrono::high_resolution_clock::now();
	auto elapsed2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - begin2);
	std::cout << "Tiempo : " << elapsed2 << "\n";

    auto begin3 = std::chrono::high_resolution_clock::now();
	occ_here::c90::TTB tt_c90testB1[10];
	auto end3 = std::chrono::high_resolution_clock::now();
	auto elapsed3 = std::chrono::duration_cast<std::chrono::milliseconds>(end3 - begin3);
	std::cout << "Tiempo : " << elapsed3 << "\n";

	auto p1 = tt_c90testB1[3].get(1,3);*/

	std::cout << "///>>>B section\n\n\n";
	///>>>B

	/*size_t amount_graphic = 29;
	char symbols_graphic[amount_graphic];
	size_t position = 0;
	for(size_t i = '!'; i < '$'; i++,position++)
	{
		//std::cout << position << ".- " << (char)i << "\n";
		symbols_graphic[position] = i;
	}
	for(size_t i = '%'; i < '0'; i++,position++)
	{
		//std::cout << position << ".- " << (char)i << "\n";
		symbols_graphic[position] = i;
	}
	for(size_t i = ':'; i < '@'; i++,position++)
	{
		//std::cout << position << ".- " << (char)i << "\n";
		symbols_graphic[position] = i;
	}
	for(size_t i = '['; i < 96; i++,position++)
	{
		//std::cout << position << ".- " << (char)i << "\n";
		symbols_graphic[position] = i;
	}
	for(size_t i = '{'; i < 127; i++,position++)
	{
		//std::cout << position << ".- " << (char)i << "\n";
		symbols_graphic[position] = i;
	}
	const char* end = symbols_graphic + 29;
	const char* symbols = symbols_graphic;
	for (size_t k = 0; k < 29; k++)
	{
		if (std::find(symbols, end, symbols[k]) == end)
		{
			std::cout  << k << ".- " << "Not found : '" << symbols_graphic[k] << "'\n";
		}
		else
		{
			std::cout  << k << ".- " << "Fount : '" << symbols_graphic[k] << "'\n";
		}
		//std::cout << k << ".- " << symbols_graphic[k] << "\n";
	}*/

	/*size_t position = 0;
	for(size_t i = ' '; i < '$'; i++,position++)
	{
		//symbols_end_words[position] = i;
		std::cout << position << ".- '" << (char)i << "'\n";
	}
	for(size_t i = '%'; i < '0'; i++,position++)
	{
		//symbols_end_words[position] = i;
		std::cout << position << ".- '" << (char)i << "'\n";
	}
	for(size_t i = ':'; i < '@'; i++,position++)
	{
		//symbols_end_words[position] = i;
		std::cout << position << ".- '" << (char)i << "'\n";
	}
	for(size_t i = '['; i < 96; i++,position++)
	{
		//symbols_end_words[position] = i;
		std::cout << position << ".- '" << (char)i << "'\n";
	}
	for(size_t i = '{'; i < 127; i++,position++)
	{
		//symbols_end_words[position] = i;
		std::cout << position << ".- '" << (char)i << "'\n";
	}*/



	//constexpr auto ttb = occ_here::c90::create_lexer_b();
	constexpr const occ_here::c90::TTB ttb;
	/*
	int position = 0;
	for(size_t i = 0; i < 99; i++)
	{
		std::cout << ++position << ".-"<< ttb.get_symbols()[i] << "\n";
	}
	*/
	if(ttb.get_last_error() > core_here::lex::errors::none) std::cout << "Error detectado : " << core_here::lex::to_string(ttb.get_last_error()) << "\n";
	std::cout << "Ultimo estado creado : " << ttb.get_state_last() << "\n";
	//ttb.print(std::cout);
	/*
	for(size_t i = 0; i < ttb.get_amoun_states(); i++)
	{
		for(size_t j = 0; j < ttb.get_amoun_transitions(); j++)
		{
			if(ttb.get(i,j)->next < 0)
			{
			}
			else
			{
				std::cout << i << "--" << j << "-->" << ttb.get(i,j)->next << "\n";
			}
		}
	}
	*/
	std::filesystem::path file1_c90b = "C:\\Users\\Azael\\Documents\\develop\\octetos\\OCC\\tests\\main-ansi-90.c";
	const char* str_c90b = "auto char break switch volatil void int 923456789 5 j a0 aabcd a1_test z juan contianer09 _09cont _09cont % ? # inta main()";
	core_next::Buffer<char> buff1_c90b(str_c90b);
    core_here::lex::Tokenized<char,occ_here::c90::Tokens> tkzed;
	//constexpr auto tt_c90 = occ_here::c90::create_lexer_a();
	constexpr const occ_here::c90::TTB tt_c90b;
	/*
	std::cout << "TT listing...\n";
	tt_c90b.print(std::cout);
	std::cout << "\n";
	*/
	std::string strtk;
	core_next::lex::Lexer<char,occ_here::c90::Tokens,core_here::lex::State,occ_here::c90::TTB_BASE> lex_c90b(tt_c90b, buff1_c90b);
	//std::cout << "\n\n";
	tk_c90 = lex_c90b.next(tkzed);
	if (tk_c90 != occ_here::c90::Tokens::keyword_auto)
	{
		std::cout << "Fallo, se espera keyword auto, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	if(lex_c90b.get_string_length() != 4)
    {
        std::cout << "Tamano del es tring es incorrecto se peseraba 4\n";
    }
    //strtk = (std::string)tkzed;
    //std::cout << strtk << "\n";
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::keyword_char)
	{
		std::cout << "Fallo, se espera keywod char, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";
	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::keyword_break)
	{
		std::cout << "Fallo, se espera keywod break, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::keyword_switch)
	{
		std::cout << "Fallo, se espera keywod switch, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::keyword_volatil)
	{
		std::cout << "Fallo, se espera keywod volatil, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::keyword_void)
	{
		std::cout << "Fallo, se espera keywod void, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::keyword_int)
	{
		std::cout << "Fallo, se espera keywod int, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::integer)
	{
		std::cout << "Fallo, se espera integer, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::integer)
	{
		std::cout << "Fallo, se espera integer, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

    tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::identifier)
	{
		std::cout << "Fallo, se espera identifier, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::identifier)
	{
		std::cout << "Fallo, se espera identifier, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::identifier)
	{
		std::cout << "Fallo, se espera identifier, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::identifier)
	{
		std::cout << "Fallo, se espera identifier, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::identifier)
	{
		std::cout << "Fallo, se espera identifier, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::identifier)
	{
		std::cout << "Fallo, se espera identifier, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::identifier)
	{
		std::cout << "Fallo, se espera identifier, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::identifier)
	{
		std::cout << "Fallo, se espera identifier, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::identifier)
	{
		std::cout << "Fallo, se espera identifier, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90b.next();
	if (tk_c90 != (occ_here::c90::Tokens)'%')
	{
		std::cout << "Fallo, se espera %, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90b.next();
	if (tk_c90 != (occ_here::c90::Tokens)'?')
	{
		std::cout << "Fallo, se espera %, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90b.next();
	if (tk_c90 != (occ_here::c90::Tokens)'#')
	{
		std::cout << "Fallo, se espera %, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::identifier)
	{
		std::cout << "Fallo, se espera identifier, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != occ_here::c90::Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90b.next(tkzed);
	if (tk_c90 != occ_here::c90::Tokens::identifier)
	{
		std::cout << "Fallo, se espera identifier, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	if(lex_c90b.get_string_length() != 4)
    {
        std::cout << "Se esperaba un string de 4 caracteres, encontranron" << lex_c90b.get_string_length() << "\n";
    }
	//std::cout << "\n";

	tk_c90 = lex_c90b.next();
	if (tk_c90 != (occ_here::c90::Tokens)'(')
	{
		std::cout << "Fallo, se espera (, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90b.next();
	if (tk_c90 != (occ_here::c90::Tokens)')')
	{
		std::cout << "Fallo, se espera ), se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	std::cout << "///<<<B section\n\n\n";
	///<<<B

	return EXIT_SUCCESS;
}

