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
    prerelease,
    release,
    rtm,
    ga
};

enum octetos_version_eBuild
{
	none,
    ul_e,
    string_e
};
union octetos_version_vBuild
{
    char* string;
    unsigned long ul;
};
struct octetos_version_Build
{
    enum octetos_version_eBuild type;
    union octetos_version_vBuild value;
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
	struct octetos_version_Build build;
	enum octetos_version_Stage stage;
};

#ifdef __cplusplus  
extern "C" {
#endif 
	const char* octetos_core_Version_toString(struct octetos_Semver* version);
	void Semver_init(struct octetos_Semver* version);
const char* octetos_core_Stage_getString(enum octetos_version_Stage stage);
#ifdef __cplusplus 
}
#endif

#endif
