#include <limits.h>
#include <fstream>
#include "gtest/gtest.h"
#include <vector>
#include <string>
#include <cmath>

#include <unistd.h> //chdir

#include "EminEmaxFinder.h"

using std::vector, std::string, std::abs;

class EminEmaxTest: public testing::TestWithParam<const char*> {
protected:
	void SetUp() override {
		int rc = chdir(GetParam());
		EXPECT_TRUE(rc == 0) << "Failed to open test directory: "
				<< (GetParam()) << '\n';

		vector < string > csrFiles = { "INPUT/H.data.dat",
				"INPUT/H.indices.dat", "INPUT/H.indptr.dat" };
		EminEmaxFinder finder;
		vector<double> e_limits = finder.findEminEmax(csrFiles);
		string emin_emax_ref_filename = "REF/emin_emax.dat";
		std::fstream s(emin_emax_ref_filename, s.in);
		EXPECT_TRUE(s.is_open()) << "Failed to open " << emin_emax_ref_filename
				<< '\n';

		double emin_ref = 0, emax_ref = 0;
		if (s.is_open())
			s >> emin_ref >> emax_ref;

		double precision = 0.05;
		EXPECT_TRUE(abs((e_limits[0] - emin_ref)/emin_ref) < precision)
				<< "Emin/EminRef: " << e_limits[0] << "/" << emin_ref << '\n';
		EXPECT_TRUE(abs((e_limits[1] - emax_ref)/emax_ref) < precision)
				<< "Emax/EmaxRef: " << e_limits[1] << "/" << emax_ref << '\n';
		chdir("..");
	}
};

namespace {

//const char* pets[] = {"cat", "dog"};
//INSTANTIATE_TEST_SUITE_P(Pets, FooTest, testing::ValuesIn(pets));
string test_dir = "../test_systems/";
const char *test_systems[] = { "CG1", "atom_20k_300T" };
TEST(TestFolder, ChDR) {
	int rc = chdir(test_dir.c_str());
	EXPECT_TRUE(rc == 0) << "Failed to open test directory: " << (test_dir)
			<< '\n';
}

TEST_P(EminEmaxTest, CSR) {
}

//INSTANTIATE_TEST_SUITE_P(Whatever, EminEmaxTest, testing::Values("CG1", "atom_20k_300T"));
INSTANTIATE_TEST_SUITE_P(AllSystems, EminEmaxTest,
		testing::ValuesIn(test_systems));

}
