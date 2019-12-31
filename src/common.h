#ifndef OCTETOS_CORE_COMMON_H
#define OCTETOS_CORE_COMMON_H

enum octetos_version_Stage {
    unknown,
    developing,
    snapshot,  
    alpha,
    beta,
    betarelease,
    rc,
    release,
    rtm,
    ga
};

enum octetos_Semver_Build_Type
{
	none,
    ul_e,
    string_e
};
union octetos_Semver_Build_Value
{
    char* string;
    unsigned long ul;
};
/**
* \brief Paramaetro pasado a la funcion toString para determinar el formato de texto geneerado
* */
enum octetos_Semver_FormatString
{
	FullString,
	OnlyNumber
};
struct octetos_Semver_Build
{
    enum octetos_Semver_Build_Type type;
    union octetos_Semver_Build_Value value;
};
/**
* \brief Informacion de version
* 
**/
struct octetos_Semver {
	short major;
	short minor;
	short patch;
	short tweak;
    short stageNumber;
	struct octetos_Semver_Build build;
	enum octetos_version_Stage stage;
};

#ifdef __cplusplus  
extern "C" {
#endif 
	const char* octetos_Semver_toString(const struct octetos_Semver* version,enum octetos_Semver_FormatString);
	void octetos_Semver_init(struct octetos_Semver* version);
	
	const char* octetos_Stage_getString(enum octetos_version_Stage stage);
#ifdef __cplusplus 
}
#endif

#endif
