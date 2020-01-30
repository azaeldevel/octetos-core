#ifndef OCTETOS_CORE_COMMON_H
#define OCTETOS_CORE_COMMON_H

enum octetos_core_Stage {
    unknown,
    developing,
    snapshot,  
    alpha,
    beta,
    betarelease,
    rc,
    prerelease,
    release,
    rtm,
    ga
};
/**
* \brief Paramaetro pasado a la funcion toString para determinar el formato de texto geneerado
* */
enum octetos_core_Semver_FormatString
{
	FullString,
	OnlyNumber
};
typedef short octetos_core_semver_Number;
/**
* \brief Informacion de version
* 
**/
struct octetos_core_Semver {
	octetos_core_semver_Number major;
	octetos_core_semver_Number minor;
	octetos_core_semver_Number patch;
	const char* prerelease;
	enum octetos_core_Stage prStage;
	const char* prStringStage;
	octetos_core_semver_Number prNumber;
	const char* build;
};

#ifdef __cplusplus  
extern "C" {
#endif 
	const char* octetos_core_Semver_toString(const struct octetos_core_Semver* version,enum octetos_core_Semver_FormatString);
	void octetos_core_Semver_init(struct octetos_core_Semver* version);
	const char* octetos_core_Semver_setPrerelease(struct octetos_core_Semver* version,const char*);
	const char* octetos_core_Semver_setBuild(struct octetos_core_Semver* version,const char*);	
#ifdef __cplusplus 
}
#endif

#endif
