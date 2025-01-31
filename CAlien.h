#ifndef CALIEN_H
#define CALIEN_H
//-----------------------------------------------------------------------
//
//  Name: CAlien.h
//
//  Author: Mat Buckland 2002
//
//  Desc: class to define a space invader type alien. The alien has a 
//        neural net for a brain which controls its movement.
//
//-----------------------------------------------------------------------

#include <vector>
#include <windows.h>

#include "defines.h"
#include "utils.h"
#include "C2DMatrix.h"
#include "CBullet.h"
#include "CParams.h"
#include "SVector2D.h"
#include "NEAT.h" // Assumed NEAT library

using namespace std;

//------------------------------------------------------------------------
//
// class to define an alien 
//------------------------------------------------------------------------

// Enumerated type to define the actions the alien can perform each frame
enum action_type { thrust_left, thrust_right, thrust_up, drift };

class CAlien {

private:

    // The neural network phenotype created from the genome
    NEAT::Phenotype m_brain;

    // The genome representing the alien's neural network
    NEAT::Genome m_genome;

    // Its position in the world
    SVector2D m_vPos;

    SVector2D m_vVelocity;

    // Its scale
    double m_dScale;

    // Its mass
    double m_dMass;

    // Its age (= its fitness)
    int m_iAge;

    // Its fitness score
    double m_fitness;

    // Its bounding box (for collision detection)
    RECT m_AlienBBox;

    // Vertex buffer for the alien's local coordinates
    vector<SPoint> m_vecAlienVB;

    // Vertex buffer to hold the alien's transformed vertices
    vector<SPoint> m_vecAlienVBTrans;

    // When set to true a warning is displayed informing of
    // an input size mismatch to the neural net.
    bool m_bWarning;

    // Sets up the transformation matrices for the alien
    void WorldTransform();

    // Checks for collision with any active bullets. Returns true if
    // a collision is detected
    bool CheckForCollision(const vector<CBullet>& bullets) const;

    // Updates the alien's neural network and returns its next action
    action_type GetActionFromNetwork(const vector<CBullet>& bullets, const SVector2D& GunPos);

    // Overload '<' used for sorting
    friend bool operator<(const CAlien& lhs, const CAlien& rhs) {
        return (lhs.m_fitness > rhs.m_fitness);
    }

public:
    // Constructor accepting a genome
    CAlien(NEAT::Genome genome);

    // Renders the alien
    void Render(HDC& surface, HPEN& GreenPen, HPEN& RedPen);

    // Queries the alien's brain and updates its position accordingly
    bool Update(vector<CBullet>& bullets, const SVector2D& GunPos);

    // Resets any relevant member variables ready for a new run
    void Reset();

    // Mutates the connection weights in the alien's neural net
    void Mutate();

    // Accessor methods
    SVector2D Pos() const { return m_vPos; }
    double Fitness() const { return m_fitness; }
    void AddFitness(double fit) { m_fitness += fit; } // Increment fitness score
    NEAT::Genome GetGenome() const { return m_genome; }
};

#endif
