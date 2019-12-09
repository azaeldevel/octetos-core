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
struct octetos_version_Version {
	short major;
	short minor;
	short patch;
	short tweak;
    short stageNumber;
	struct octetos_version_Build build;
	enum octetos_version_Stage stage;
};

const char* octetos_version_getString(enum octetos_version_Stage stage);

#endif
