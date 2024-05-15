#ifndef CGENOME_H
#define CGENOME_H

#include <vector>
#include "genes.h"
#include "utils.h"

class CGenome {
private:
    int genomeID;
    std::vector<SNeuronGene> neurons;
    std::vector<SLinkGene> links;
    double fitness;

public:
    CGenome(int id);
    void addNeuronGene(const SNeuronGene& gene);
    void addLinkGene(const SLinkGene& gene);
    void mutate();
    double getFitness() const;
    void setFitness(double f);
    void clear();
};

#endif // CGENOME_H
