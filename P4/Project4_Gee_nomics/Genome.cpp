#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
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
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
	// TODO: This compiles, but may not be correct
}

bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes)
{
	// TODO
	return false;  // This compiles, but may not be correct
}

int GenomeImpl::length() const
{
	// TODO
	return 0;  // This compiles, but may not be correct
}

string GenomeImpl::name() const
{
	// TODO
	return "";  // This compiles, but may not be correct
}

bool GenomeImpl::extract(int position, int length, string& fragment) const
{
	// TODO
	return false;  // This compiles, but may not be correct
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
