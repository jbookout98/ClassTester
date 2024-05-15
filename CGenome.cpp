#include "CGenome.h"
#include <cstdlib>

CGenome::CGenome(int id) : genomeID(id), fitness(0.0) {}

void CGenome::addNeuronGene(const SNeuronGene& gene) {
    neurons.push_back(gene);
}

void CGenome::addLinkGene(const SLinkGene& gene) {
    links.push_back(gene);
}

void CGenome::mutate() {
    for (auto& link : links) {
        double mutationFactor = (rand() / double(RAND_MAX)) * 0.2 - 0.1; // Small random change
        link.mutateWeight(mutationFactor);
    }
}

double CGenome::getFitness() const {
    return fitness;
}

void CGenome::setFitness(double f) {
    fitness = f;
}

void CGenome::clear() {
    neurons.clear();
    links.clear();
}
