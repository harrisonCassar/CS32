/*
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
	//Inserting fragment: "ACT" for Genome #1 at position 0
	//Inserting fragment: "CTG" for Genome #1 at position 1
	//Inserting fragment: "TCG" for Genome #2 at position 0
	//Inserting fragment: "CGA" for Genome #2 at position 1
	//Inserting fragment: "GAC" for Genome #2 at position 2
	//Inserting fragment: "ACT" for Genome #2 at position 3
	//Inserting fragment: "TCT" for Genome #3 at position 0
	//Inserting fragment: "CTC" for Genome #3 at position 1
	//Inserting fragment: "TCG" for Genome #3 at position 2

	GenomeMatcher specTest(4);
	Genome genome1("Genome 1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC");
	Genome genome2("Genome 2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG");
	Genome genome3("Genome 3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA");

	specTest.addGenome(genome1);
	specTest.addGenome(genome2);
	specTest.addGenome(genome3);

	std::vector<DNAMatch> matches;
	bool result;

	//=======================================================
	result = specTest.findGenomesWithThisDNA("GAAG", 4, true, matches);

	cerr << "result: ";
	if (result)
		cerr << "true";
	else
		cerr << "false";

	cerr << "; matches:" << endl;

	for (std::vector<DNAMatch>::iterator itt = matches.begin(); itt != matches.end(); itt++)
	{
		cerr << itt->genomeName << " of length " << itt->length << " at position " << itt->position << endl;
	}
	//======================================================
	result = specTest.findGenomesWithThisDNA("GAATAC", 4, true, matches);

	cerr << "result: ";
	if (result)
		cerr << "true";
	else
		cerr << "false";

	cerr << "; matches:" << endl;

	for (std::vector<DNAMatch>::iterator itt = matches.begin(); itt != matches.end(); itt++)
	{
		cerr << itt->genomeName << " of length " << itt->length << " at position " << itt->position << endl;
	}
	//======================================================
	result = specTest.findGenomesWithThisDNA("GAATAC", 6, true, matches);

	cerr << "result: ";
	if (result)
		cerr << "true";
	else
		cerr << "false";

	cerr << "; matches:" << endl;

	for (std::vector<DNAMatch>::iterator itt = matches.begin(); itt != matches.end(); itt++)
	{
		cerr << itt->genomeName << " of length " << itt->length << " at position " << itt->position << endl;
	}
	//======================================================
	result = specTest.findGenomesWithThisDNA("GAATAC", 6, false, matches);

	cerr << "result: ";
	if (result)
		cerr << "true";
	else
		cerr << "false";

	cerr << "; matches:" << endl;

	for (std::vector<DNAMatch>::iterator itt = matches.begin(); itt != matches.end(); itt++)
	{
		cerr << itt->genomeName << " of length " << itt->length << " at position " << itt->position << endl;
	}
	//======================================================
	result = specTest.findGenomesWithThisDNA("GTATAT", 6, false, matches);

	cerr << "result: ";
	if (result)
		cerr << "true";
	else
		cerr << "false";

	cerr << "; matches:" << endl;

	for (std::vector<DNAMatch>::iterator itt = matches.begin(); itt != matches.end(); itt++)
	{
		cerr << itt->genomeName << " of length " << itt->length << " at position " << itt->position << endl;
	}
	//======================================================
	result = specTest.findGenomesWithThisDNA("GAATACG", 6, false, matches);

	cerr << "result: ";
	if (result)
		cerr << "true";
	else
		cerr << "false";

	cerr << "; matches:" << endl;

	for (std::vector<DNAMatch>::iterator itt = matches.begin(); itt != matches.end(); itt++)
	{
		cerr << itt->genomeName << " of length " << itt->length << " at position " << itt->position << endl;
	}
	//======================================================
	result = specTest.findGenomesWithThisDNA("GAAGGGTT", 5, false, matches);

	cerr << "result: ";
	if (result)
		cerr << "true";
	else
		cerr << "false";

	cerr << "; matches:" << endl;

	for (std::vector<DNAMatch>::iterator itt = matches.begin(); itt != matches.end(); itt++)
	{
		cerr << itt->genomeName << " of length " << itt->length << " at position " << itt->position << endl;
	}
	//======================================================
	result = specTest.findGenomesWithThisDNA("GAAGGGTT", 6, false, matches);

	cerr << "result: ";
	if (result)
		cerr << "true";
	else
		cerr << "false";

	cerr << "; matches:" << endl;

	for (std::vector<DNAMatch>::iterator itt = matches.begin(); itt != matches.end(); itt++)
	{
		cerr << itt->genomeName << " of length " << itt->length << " at position " << itt->position << endl;
	}
	//======================================================
	result = specTest.findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCC", 12, false, matches);

	cerr << "result: ";
	if (result)
		cerr << "true";
	else
		cerr << "false";

	cerr << "; matches:" << endl;

	for (std::vector<DNAMatch>::iterator itt = matches.begin(); itt != matches.end(); itt++)
	{
		cerr << itt->genomeName << " of length " << itt->length << " at position " << itt->position << endl;
	}
	//======================================================
	result = specTest.findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCG", 12, false, matches);

	cerr << "result: ";
	if (result)
		cerr << "true";
	else
		cerr << "false";

	cerr << "; matches:" << endl;

	for (std::vector<DNAMatch>::iterator itt = matches.begin(); itt != matches.end(); itt++)
	{
		cerr << itt->genomeName << " of length " << itt->length << " at position " << itt->position << endl;
	}
	//======================================================
	result = specTest.findGenomesWithThisDNA("GAAG", 3, true, matches);

	cerr << "result: ";
	if (result)
		cerr << "true";
	else
		cerr << "false";

	cerr << "; matches:" << endl;

	for (std::vector<DNAMatch>::iterator itt = matches.begin(); itt != matches.end(); itt++)
	{
		cerr << itt->genomeName << " of length " << itt->length << " at position " << itt->position << endl;
	}
	//======================================================
	result = specTest.findGenomesWithThisDNA("GAAG", 5, true, matches);

	cerr << "result: ";
	if (result)
		cerr << "true";
	else
		cerr << "false";

	cerr << "; matches:" << endl;

	for (std::vector<DNAMatch>::iterator itt = matches.begin(); itt != matches.end(); itt++)
	{
		cerr << itt->genomeName << " of length " << itt->length << " at position " << itt->position << endl;
	}
	//======================================================

	return 0;
}
*/

#include "provided.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
using namespace std;

#if defined(_MSC_VER)  &&  !defined(_DEBUG)
#include <iostream>
#include <windows.h>
#include <conio.h>

struct KeepWindowOpenUntilDismissed
{
	~KeepWindowOpenUntilDismissed()
	{
		DWORD pids[1];
		if (GetConsoleProcessList(pids, 1) == 1)
		{
			std::cout << "Press any key to continue . . . ";
			_getch();
		}
	}
} keepWindowOpenUntilDismissed;
#endif

// Change the string literal in this declaration to be the path to the
// directory that contains the genome data files we provide, e.g.,
// "Z:/CS32/Geenomics/data" or "/Users/fred/cs32/Geenomics/data"

const string PROVIDED_DIR = "../data";

const string providedFiles[] = {
	"Ferroplasma_acidarmanus.txt",
	"Halobacterium_jilantaiense.txt",
	"Halorubrum_chaoviator.txt",
	"Halorubrum_californiense.txt",
	"Halorientalis_regularis.txt",
	"Halorientalis_persicus.txt",
	"Ferroglobus_placidus.txt",
	"Desulfurococcus_mucosus.txt"
};

void createNewLibrary(GenomeMatcher*& library)
{
	cout << "Enter minimum search length (3-100): ";
	string line;
	getline(cin, line);
	int len = atoi(line.c_str());
	if (len < 3 || len > 100)
	{
		cout << "Invalid prefix size." << endl;
		return;
	}
	delete library;
	library = new GenomeMatcher(len);
}

void addOneGenomeManually(GenomeMatcher* library)
{
	cout << "Enter name: ";
	string name;
	getline(cin, name);
	if (name.empty())
	{
		cout << "Name must not be empty." << endl;
		return;
	}
	cout << "Enter DNA sequence: ";
	string sequence;
	getline(cin, sequence);
	if (sequence.empty())
	{
		cout << "Sequence must not be empty." << endl;
		return;
	}
	if (sequence.find_first_not_of("ACGTNacgtn") != string::npos)
	{
		cout << "Invalid character in DNA sequence." << endl;
		return;
	}
	for (char ch : sequence)
		ch = toupper(ch);
	library->addGenome(Genome(name, sequence));
}

bool loadFile(string filename, vector<Genome>& genomes)
{
	ifstream inputf(filename);
	if (!inputf)
	{
		cout << "Cannot open file: " << filename << endl;
		return false;
	}
	if (!Genome::load(inputf, genomes))
	{
		cout << "Improperly formatted file: " << filename << endl;
		return false;
	}
	return true;
}

void loadOneDataFile(GenomeMatcher* library)
{
	string filename;
	cout << "Enter file name: ";
	getline(cin, filename);
	if (filename.empty())
	{
		cout << "No file name entered." << endl;
		return;
	}
	vector<Genome> genomes;
	if (!loadFile(filename, genomes))
		return;
	for (const auto& g : genomes)
		library->addGenome(g);
	cout << "Successfully loaded " << genomes.size() << " genomes." << endl;
}

void loadProvidedFiles(GenomeMatcher* library)
{
	for (const string& f : providedFiles)
	{
		vector<Genome> genomes;
		if (loadFile(PROVIDED_DIR + "/" + f, genomes))
		{
			for (const auto& g : genomes)
				library->addGenome(g);
			cout << "Loaded " << genomes.size() << " genomes from " << f << endl;
		}
	}
}

void findGenome(GenomeMatcher* library, bool exactMatch)
{
	if (exactMatch)
		cout << "Enter DNA sequence for which to find exact matches: ";
	else
		cout << "Enter DNA sequence for which to find exact matches and SNiPs: ";
	string sequence;
	getline(cin, sequence);
	int minLength = library->minimumSearchLength();
	if (sequence.size() < minLength)
	{
		cout << "DNA sequence length must be at least " << minLength << endl;
		return;
	}
	cout << "Enter minimum sequence match length: ";
	string line;
	getline(cin, line);
	int minMatchLength = atoi(line.c_str());
	if (minMatchLength > sequence.size())
	{
		cout << "Minimum match length must be at least the sequence length." << endl;
		return;
	}
	vector<DNAMatch> matches;
	if (!library->findGenomesWithThisDNA(sequence, minMatchLength, exactMatch, matches))
	{
		cout << "No ";
		if (exactMatch)
			cout << " matches";
		else
			cout << " matches or SNiPs";
		cout << " of " << sequence << " were found." << endl;
		return;
	}
	cout << matches.size();
	if (exactMatch)
		cout << " matches";
	else
		cout << " matches and/or SNiPs";
	cout << " of " << sequence << " found:" << endl;
	for (const auto& m : matches)
		cout << "  length " << m.length << " position " << m.position << " in " << m.genomeName << endl;
}

bool getFindRelatedParams(double& pct, bool& exactMatchOnly)
{
	cout << "Enter match percentage threshold (0-100): ";
	string line;
	getline(cin, line);
	pct = atof(line.c_str());
	if (pct < 0 || pct > 100)
	{
		cout << "Percentage must be in the range 0 to 100." << endl;
		return false;
	}
	cout << "Require (e)xact match or allow (S)NiPs (e or s): ";
	getline(cin, line);
	if (line.empty() || (line[0] != 'e' && line[0] != 's'))
	{
		cout << "Response must be e or s." << endl;
		return false;
	}
	exactMatchOnly = (line[0] == 'e');
	return true;
}

void findRelatedGenomesManual(GenomeMatcher* library)
{
	cout << "Enter DNA sequence: ";
	string sequence;
	getline(cin, sequence);
	int minLength = library->minimumSearchLength();
	if (sequence.size() < minLength)
	{
		cout << "DNA sequence length must be at least " << minLength << endl;
		return;
	}
	double pctThreshold;
	bool exactMatchOnly;
	if (!getFindRelatedParams(pctThreshold, exactMatchOnly))
		return;

	vector<GenomeMatch> matches;
	library->findRelatedGenomes(Genome("x", sequence), 2 * minLength, exactMatchOnly, pctThreshold, matches);
	if (matches.empty())
	{
		cout << "    No related genomes were found" << endl;
		return;
	}
	cout << "    " << matches.size() << " related genomes were found:" << endl;
	cout.setf(ios::fixed);
	cout.precision(2);
	for (const auto& m : matches)
		cout << " " << setw(6) << m.percentMatch << "%  " << m.genomeName << endl;
}

void findRelatedGenomesFromFile(GenomeMatcher* library)
{
	string filename;
	cout << "Enter name of file containing one or more genomes to find matches for: ";
	getline(cin, filename);
	if (filename.empty())
	{
		cout << "No file name entered." << endl;
		return;
	}
	vector<Genome> genomes;
	if (!loadFile(filename, genomes))
		return;
	double pctThreshold;
	bool exactMatchOnly;
	if (!getFindRelatedParams(pctThreshold, exactMatchOnly))
		return;

	int minLength = library->minimumSearchLength();
	for (const auto& g : genomes)
	{
		vector<GenomeMatch> matches;
		library->findRelatedGenomes(g, 2 * minLength, exactMatchOnly, pctThreshold, matches);
		cout << "  For " << g.name() << endl;
		if (matches.empty())
		{
			cout << "    No related genomes were found" << endl;
			continue;
		}
		cout << "    " << matches.size() << " related genomes were found:" << endl;
		cout.setf(ios::fixed);
		cout.precision(2);
		for (const auto& m : matches)
			cout << "     " << setw(6) << m.percentMatch << "%  " << m.genomeName << endl;
	}
}

void showMenu()
{
	cout << "        Commands:" << endl;
	cout << "         c - create new genome library      s - find matching SNiPs" << endl;
	cout << "         a - add one genome manually        r - find related genomes (manual)" << endl;
	cout << "         l - load one data file             f - find related genomes (file)" << endl;
	cout << "         d - load all provided data files   ? - show this menu" << endl;
	cout << "         e - find matches exactly           q - quit" << endl;
}

int main()
{
	const int defaultMinSearchLength = 10;

	cout << "Welcome to the Gee-nomics test harness!" << endl;
	cout << "The genome library is initially empty, with a default minSearchLength of " << defaultMinSearchLength << endl;
	showMenu();

	GenomeMatcher* library = new GenomeMatcher(defaultMinSearchLength);

	for (;;)
	{
		cout << "Enter command: ";
		string command;
		if (!getline(cin, command))
			break;
		if (command.empty())
			continue;
		switch (tolower(command[0]))
		{
		default:
			cout << "Invalid command " << command << endl;
			break;
		case 'q':
			delete library;
			return 0;
		case '?':
			showMenu();
			break;
		case 'c':
			createNewLibrary(library);
			break;
		case 'a':
			addOneGenomeManually(library);
			break;
		case 'l':
			loadOneDataFile(library);
			break;
		case 'd':
			loadProvidedFiles(library);
			break;
		case 'e':
			findGenome(library, true);
			break;
		case 's':
			findGenome(library, false);
			break;
		case 'r':
			findRelatedGenomesManual(library);
			break;
		case 'f':
			findRelatedGenomesFromFile(library);
			break;
		}
	}
}