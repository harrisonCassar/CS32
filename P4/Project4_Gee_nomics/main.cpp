#include <iostream>
#include <cassert>
#include <fstream>
#include "provided.h";
#include "Trie.h";
using namespace std;

int main()
{
	//Trie.h tests

	//Genome.cpp tests
	//load() tests:
	ifstream infile0("D:/GitHub/CS32/P4/data/testdata/test0.txt");
	ifstream infile1("D:/GitHub/CS32/P4/data/testdata/test1.txt");
	ifstream infile2("D:/GitHub/CS32/P4/data/testdata/test2.txt");
	ifstream infile2pt2("D:/GitHub/CS32/P4/data/testdata/test2_part2.txt");
	ifstream infile3("D:/GitHub/CS32/P4/data/testdata/test3.txt");
	ifstream infile4("D:/GitHub/CS32/P4/data/testdata/test4.txt");
	ifstream infile5("D:/GitHub/CS32/P4/data/testdata/test5.txt");
	ifstream infile6("D:/GitHub/CS32/P4/data/testdata/test6.txt");
	ifstream infile7("D:/GitHub/CS32/P4/data/testdata/test7.txt");
	ifstream infile8("D:/GitHub/CS32/P4/data/testdata/test8.txt");
	ifstream infile9("D:/GitHub/CS32/P4/data/testdata/test8.txt");
	ifstream infile10("D:/GitHub/CS32/P4/data/testdata/test10.txt");
	ifstream infile11("D:/GitHub/CS32/P4/data/testdata/test11.txt");
	ifstream infile14("D:/GitHub/CS32/P4/data/testdata/test14.txt");
	ifstream infile15("D:/GitHub/CS32/P4/data/testdata/test15.txt");
	ifstream infile16("D:/GitHub/CS32/P4/data/testdata/test16.txt");

	//these three are all the same path but different infile## because can only use infile## once, and file is used 3 times
	ifstream infile17("D:/GitHub/CS32/P4/data/testdata/test17.txt");
	ifstream infile18("D:/GitHub/CS32/P4/data/testdata/test17.txt");
	ifstream infile19("D:/GitHub/CS32/P4/data/testdata/test17.txt");
	
	if (!infile17)
		cerr << "couldn't open file!" << endl;
	
	vector<Genome> genomes;

	assert(Genome::load(infile0, genomes) == true);
	assert(Genome::load(infile1, genomes) == false);
	assert(Genome::load(infile2, genomes) == false);
	assert(Genome::load(infile2pt2, genomes) == false);
	assert(Genome::load(infile3, genomes) == false);
	assert(Genome::load(infile4, genomes) == false);
	assert(Genome::load(infile5, genomes) == false);
	assert(Genome::load(infile6, genomes) == true);
	assert(Genome::load(infile7, genomes) == false);
	assert(Genome::load(infile8, genomes) == false);
	assert(Genome::load(infile9, genomes) == false);
	assert(Genome::load(infile10, genomes) == false);
	assert(Genome::load(infile11, genomes) == false);
	assert(Genome::load(infile14, genomes) == false);
	assert(Genome::load(infile15, genomes) == false);
	assert(Genome::load(infile16, genomes) == false);
	assert(Genome::load(infile17, genomes) == true);

	genomes.clear();
	Genome::load(infile18, genomes);
	cerr << "genomes in main empty check: " << genomes.empty() << endl;

	assert(genomes.empty() == false);
	
	
	genomes.clear();
	Genome temp_genome("bigboi", "ATCGN");
	genomes.push_back(temp_genome);
	Genome::load(infile19, genomes);

	vector<Genome>::iterator it = genomes.begin();
	assert(it->name() != "bigboi");

	cerr << endl << endl << "===============================================================================" << endl << endl << endl;

	//GenomeMatcher.cpp tests:
	//for this test, add in a cerr statement right before you call your Trie's insert() method
	//cerr << "Inserting fragment: \"" << fragment << "\" for Genome #" << m_curGenomeNum << " at position " << i << endl;
	GenomeMatcher temp_matcher(3);

	Genome temp1("First", "ACTG");
	Genome temp2("Second", "TCGACT");
	Genome temp3("Third", "TCTCG");

	temp_matcher.addGenome(temp1);
	temp_matcher.addGenome(temp2);
	temp_matcher.addGenome(temp3);

	//test 1 expected output:
	/*
	Inserting fragment: "ACT" for Genome #1 at position 0
	Inserting fragment: "CTG" for Genome #1 at position 1
	Inserting fragment: "TCG" for Genome #2 at position 0
	Inserting fragment: "CGA" for Genome #2 at position 1
	Inserting fragment: "GAC" for Genome #2 at position 2
	Inserting fragment: "ACT" for Genome #2 at position 3
	Inserting fragment: "TCT" for Genome #3 at position 0
	Inserting fragment: "CTC" for Genome #3 at position 1
	Inserting fragment: "TCG" for Genome #3 at position 2
	*/

	return 0;
}
