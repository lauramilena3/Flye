//(c) 2016 by Authors
//This file is a part of ABruijn program.
//Released under the BSD license (see LICENSE file)

#pragma once

#include "fasta.h"
#include "overlap.h"
#include "chimera.h"

struct ContigPath
{
	ContigPath(): 
		circular(false) {}
	ContigPath(ContigPath && other): 
		circular(other.circular) 
	{reads.swap(other.reads);}

	std::vector<FastaRecord::Id> reads;
	bool circular;
};

class Extender
{
public:
	Extender(const OverlapDetector& ovlpDetector, 
			 const ChimeraDetector& chimDetector,
			 const SequenceContainer& seqContainer):
		_ovlpDetector(ovlpDetector), _chimDetector(chimDetector),
		_seqContainer(seqContainer)
	{}

	void assembleContigs();
	const std::vector<ContigPath>& getContigPaths() const
		{return _contigPaths;}

private:
	const OverlapDetector& _ovlpDetector;
	const ChimeraDetector& _chimDetector;
	const SequenceContainer& _seqContainer;

	FastaRecord::Id stepRight(FastaRecord::Id readId, 
									  FastaRecord::Id startReadId);
	ContigPath extendRead(FastaRecord::Id readId);

	bool  isProperRightExtension(const OverlapRange& ovlp);
	bool  isProperLeftExtension(const OverlapRange& ovlp);
	float branchIndex(FastaRecord::Id readId);
	int   countRightExtensions(FastaRecord::Id readId);

	std::vector<ContigPath> _contigPaths;
	std::unordered_set<FastaRecord::Id>	_visitedReads;
};