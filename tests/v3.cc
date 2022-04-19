

#include "v3.hh"

#include <Exception-v3.hh>
#include <Version-v3.hh>

using namespace oct::core::v3;

void v3_developing()
{
	Exception ex1;
	CU_ASSERT(ex1.code() == 0);
}

void v3_reduced_parser()
{
	Semver ver15;
	CU_ASSERT(ver15.parse("5.30"));
	CU_ASSERT(ver15.getMajor() == 5);
	CU_ASSERT(ver15.getMinor() == 30);

	Semver ver16;
	CU_ASSERT(ver16.parse("5.30-alpha"));
	CU_ASSERT(ver16.getMajor() == 5);
	CU_ASSERT(ver16.getMinor() == 30);
	CU_ASSERT(strcmp(ver16.getPrerelease(),"alpha") == 0);

	Semver ver17;
	CU_ASSERT(ver17.parse("5.30-alpha+mountain"));
	CU_ASSERT(ver17.getMajor() == 5);
	CU_ASSERT(ver17.getMinor() == 30);
	CU_ASSERT(strcmp(ver17.getPrerelease(),"alpha") == 0);
	CU_ASSERT(strcmp(ver17.getBuild(), "mountain") == 0);

	Semver ver18;
	CU_ASSERT(ver18.parse("5.30+mountain"));
	CU_ASSERT(ver18.getMajor() == 5);
	CU_ASSERT(ver18.getMinor() == 30);
	CU_ASSERT(strcmp(ver18.getBuild(), "mountain") == 0);
}