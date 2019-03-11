#include "provided.h"
#include "Trie.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <fstream>
using namespace std;

bool compareGenomeMatches(GenomeMatch a, GenomeMatch b);

class GenomeMatcherImpl
{
public:
	GenomeMatcherImpl(int minSearchLength);
	void addGenome(const Genome& genome);
	int minimumSearchLength() const;
	bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
	bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
	struct Pair
	{
		int genomeNum;
		int position;
	};

	struct MaxMatchCandidate
	{
		string genomeName;
		int length;
		int position;
	};

	Trie<Pair> m_data;
	int m_minSearchLength;
	vector<Genome> m_genomes;
	int m_curGenomeNum;
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength) : m_minSearchLength(minSearchLength), m_curGenomeNum(0) {}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
	m_genomes.push_back(genome);
	m_curGenomeNum++;

	for (int i = 0; i <= genome.length() - minimumSearchLength(); i++)
	{
		string fragment;
		if (!genome.extract(i, minimumSearchLength(), fragment))
			return;

		Pair temp = { m_curGenomeNum, i };

		cerr << "Inserting fragment: \"" << fragment << "\" for Genome #" << m_curGenomeNum << " at position " << i << endl;
		m_data.insert(fragment,temp);
	}
}

int GenomeMatcherImpl::minimumSearchLength() const
{
	return m_minSearchLength;
}

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
	if (minimumLength < 0)
		return false;
	if (minimumLength < minimumSearchLength() || fragment.size() < (unsigned int)minimumLength)
		return false;

	bool foundMatch = false;

	matches.clear();
	map<string, DNAMatch> maxLengthGenomeMatch;

	vector<Pair> potentialMatches = m_data.find(fragment.substr(0, minimumSearchLength()), exactMatchOnly);

	for (vector<Pair>::iterator it = potentialMatches.begin(); it != potentialMatches.end(); it++)
	{
		string extraction = "";

		bool successfulExtraction = false;
		
		//try to extract largest possible substr that still is >= to minimum match length
		for (int i = fragment.size(); !successfulExtraction && i >= minimumLength; i--)
		{
			if (m_genomes[it->genomeNum].extract(it->position, i, extraction))
				successfulExtraction = true;
		}

		//if no extraction made, then potential match is invalid; continue to next
		if (!successfulExtraction)
			continue;

		int candidateLength = 0;
		int alterationDegree = 0;

		//if SNiPS are allowed
		if (!exactMatchOnly)
			alterationDegree = 1;

		//iterate through characters, watching for SNiPS if needed, and checking length of potential match
		for (unsigned int i = 0; i < extraction.size(); i++)
		{
			if (extraction[i] != fragment[i])
			{
				if (alterationDegree == 1)
					alterationDegree--;
				else
					break;
			}

			candidateLength++;
		}
		
		//if valid length for a match, then check if it is greater than previous DNA match for that Genome
		if (candidateLength >= minimumLength)
		{
			map<string, DNAMatch>::iterator itmap = maxLengthGenomeMatch.find(m_genomes[it->genomeNum].name());
			if (itmap != maxLengthGenomeMatch.end())
			{
				//check if candidate is strictly greater than mapped current value; replace if yes
				if (candidateLength > itmap->second.length)
				{
					itmap->second.length = candidateLength;
					itmap->second.position = it->position;
				}
				else if (candidateLength == itmap->second.length) //if equal, replace if position is earlier in Genome
				{
					if (it->position < itmap->second.position)
						itmap->second.position = it->position;
				}
			}
			else
			{
				DNAMatch temp = { m_genomes[it->genomeNum].name(),candidateLength,it->position };
				maxLengthGenomeMatch[temp.genomeName] = temp;
			}

			foundMatch = true;
		}
	}

	//since correct maxes are already found in map, just copy over DNAMatches
	for (map<string, DNAMatch>::iterator itmap = maxLengthGenomeMatch.begin(); itmap != maxLengthGenomeMatch.end(); itmap++)
		matches.push_back(itmap->second);

	if (foundMatch)
		return true;
	else
		return false;
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
	if (fragmentMatchLength < minimumSearchLength())
		return false;

	int numOfSequences = query.length() / fragmentMatchLength;

	results.clear();

	//running record of number of matches found for each named genome
	map<string, int> matchesFound;

	//intialize all currently-added genomes to zero
	for (unsigned int i = 0; i < m_genomes.size(); i++)
		matchesFound[m_genomes[i].name()] = 0;

	for (int i = 0; i*fragmentMatchLength < query.length(); i++)
	{
		string extraction = "";
		query.extract(i, fragmentMatchLength, extraction);

		vector<DNAMatch> matches;
		if (findGenomesWithThisDNA(extraction, fragmentMatchLength, exactMatchOnly, matches))
		{
			for (vector<DNAMatch>::iterator it = matches.begin(); it != matches.end(); it++)
				matchesFound[it->genomeName]++;
		}
	}

	for (map<string, int>::iterator itmap = matchesFound.begin(); itmap != matchesFound.end(); itmap++)
	{
		if (itmap->second == 0)
			continue;

		double p = itmap->second / double(numOfSequences);

		if (p > matchPercentThreshold)
		{
			GenomeMatch temp = { itmap->first,p };
			results.push_back(temp);
		}
	}

	//sort results, preserving stability
	sort(results.begin(), results.end(), compareGenomeMatches);

	if (results.empty())
		return false;

	return true;
}

bool compareGenomeMatches(GenomeMatch a, GenomeMatch b)
{
	//alphabetical ordering, where lowercase characters are embedded in alphabetical order: a > A > b > B...
	if (a.percentMatch == b.percentMatch)
	{
		unsigned int i = 0;
		while (i < a.genomeName.size() && i < b.genomeName.size())
		{
			if (a.genomeName[i] == b.genomeName[i])
				continue;

			if (islower(a.genomeName[i]))
			{
				if (islower(b.genomeName[i]))
					return a.genomeName[i] < b.genomeName[i];
				if (toupper(a.genomeName[i]) == b.genomeName[i])
					return true;

				return toupper(a.genomeName[i]) < b.genomeName[i];
			}

			if (isupper(a.genomeName[i]))
			{
				if (isupper(b.genomeName[i]))
					return a.genomeName[i] < b.genomeName[i];
				if (tolower(a.genomeName[i]) == b.genomeName[i])
					return false;

				return tolower(a.genomeName[i]) < b.genomeName[i];
			}

			i++;
		}

		//must be same, so smaller one
		return a.genomeName.size() < b.genomeName.size();
	}

	return a.percentMatch > b.percentMatch;
}

//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
	m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
	delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
	m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
	return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
	return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
	return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
