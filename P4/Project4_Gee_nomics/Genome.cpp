#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <cctype>
using namespace std;

//  Part    #1: You must modify the code    below   to  implement   your GenomeImpl class.
//  You may add additional  headers,    using   statements, functions   (including  a
//  destructor  if  necessary), classes,    etc.

class GenomeImpl
{
public:
	GenomeImpl(const string& nm, const string& sequence);
	static bool load(istream& genomeSource, vector<Genome>& genomes);
	int length() const;
	string name() const;
	bool extract(int position, int length, string& fragment) const;
private:
	string m_name;
	int m_length;
	string m_sequence;
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence):m_name(nm), m_length(sequence.size()), m_sequence(sequence) {}

bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes)
{
	genomes.clear();

	char c;
	if (!genomeSource.get(c))
		return false;

	bool endOfFile = false;

	while (!endOfFile) //repeat loop for each entire gene
	{
		if (c != '>')
			return false;

		string name = "";
		string sequence = "";

		getline(genomeSource, name);

		if (genomeSource.eof())
			return false;

		if (name.size() <= 0)
			return false;

		bool firstLineOfGene = true;

		while (!endOfFile) //repeat loop on each line of gene
		{
			//reset character counter
			int characterCount = 0;

			if (!genomeSource.get(c))
			{
				if (firstLineOfGene)
					return false;

				endOfFile = true;
				break;
			}

			if (c == '\n')
			{
				return false;
				/*
				if (!genomeSource.get(c))
				{
					if (firstLineOfGene)
						return false;

					endOfFile = true;
					break;
				}
				else
					return false;
					*/
			}
		
			if (c == '>')
			{
				if (firstLineOfGene)
					return false;
				else
					break;
			}

			c = toupper(c);

			if (c == 'A' || c == 'C' || c == 'G' || c == 'T' || c == 'N')
				sequence += c;
			else
				return false;

			for (;;) //repeat loop on each character in line of gene
			{
				if (!genomeSource.get(c))
				{
					endOfFile = true;
					break;
				}
				
				characterCount++;
				
				c = toupper(c);

				if (c == 'A' || c == 'C' || c == 'G' || c == 'T' || c == 'N')
					sequence += c;
				else if (c == '\n')
					break;
				else //not a valid character
					return false;
			}

			//check for valid characterCount
			cerr << "checking for character count: " << characterCount << endl;
			if (characterCount <= 0 && characterCount > 80)
				return false;

			firstLineOfGene = false;
		}

		cerr << "adding new genome to genomes vector! name: " << name << ", and sequence: " << sequence << endl;
		Genome temp(name, sequence);
		genomes.push_back(temp);
	}

	//repeating while not end of file //repeat loop on each whole gene including name
		//check for '>' character
		//extract name (whole line after '>' character)
		//enter loop for next line //repeat loop on each line in a gene
			//reset characterCount for line to 0
			//if '>' and its the first gene line, then invalid
			//if '>' and its not the first gene line, then break
			//... (among other checks)
			//check each character on line (should only be aA, cC, tT, gG, nN)
				//if valid, concatenate uppercase-variant onto sequence and increment characterCount
			//if end of line, check characterCount is > 0 and <= 80, and then repeat line loop if its not (return false if it is, as bad formatting)
		//create Genome with sequence and name
		//push back new Genome to 'genomes' vector

	cerr << "genomes in function empty check: " << genomes.empty() << endl;

	return true;
}

int GenomeImpl::length() const
{
	return m_length;
}

string GenomeImpl::name() const
{
	return m_name;
}

bool GenomeImpl::extract(int position, int length, string& fragment) const
{
	if (position < 0 || length < 0)
		return false;

	if (position + length <= this->length())
	{
		fragment = "";

		for (int i = position; i < position + length; i++)
			fragment += m_sequence[i];

		return true;
	}
	else
		return false;
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
	m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
	delete m_impl;
}

Genome::Genome(const Genome& other)
{
	m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
	GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
	delete m_impl;
	m_impl = newImpl;
	return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes)
{
	return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
	return m_impl->length();
}

string Genome::name() const
{
	return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
	return m_impl->extract(position, length, fragment);
}
