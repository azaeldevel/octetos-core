#ifndef OCTETOS_CORE_COMMON_H
#define OCTETOS_CORE_COMMON_H


/**
* \brief Paramaetro pasado a la funcion toString para determinar el formato de texto geneerado
* */
enum octetos_Semver_FormatString
{
	FullString,
	OnlyNumber
};
/**
* \brief Informacion de version
* 
**/
struct octetos_Semver {
	short major;
	short minor;
	short patch;
	const char* prerelease;
};

#ifdef __cplusplus  
extern "C" {
#endif 
	const char* octetos_Semver_toString(const struct octetos_Semver* version,enum octetos_Semver_FormatString);
	void octetos_Semver_init(struct octetos_Semver* version);
	const char* octetos_Semver_setPrerelease(struct octetos_Semver* version,const char*);
	
#ifdef __cplusplus 
}
#endif

#endif
