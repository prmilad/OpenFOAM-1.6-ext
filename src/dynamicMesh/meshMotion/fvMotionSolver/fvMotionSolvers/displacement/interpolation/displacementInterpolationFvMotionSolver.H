/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Class
    Foam::displacementInterpolationFvMotionSolver

Description
    Mesh motion solver for an fvMesh.

    Scales inbetween motion prescribed on faceZones. Works out per point
    the distance between the bounding face zones (in all three directions)
    at the start and then every time step
    - moves the faceZones based on tables
    - interpolates the displacement of all points based on the
      faceZone motion.

    Tables are in the @a constant/tables directory.

Note
    could be a motionSolver - does not use any fvMesh structure.

SourceFiles
    displacementInterpolationFvMotionSolver.C

\*---------------------------------------------------------------------------*/

#ifndef displacementInterpolationFvMotionSolver_H
#define displacementInterpolationFvMotionSolver_H

#include "displacementFvMotionSolver.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
        Class displacementInterpolationFvMotionSolver Declaration
\*---------------------------------------------------------------------------*/

class displacementInterpolationFvMotionSolver
:
    public displacementFvMotionSolver
{
    // Private data

        //- Additional settings for motion solver
        dictionary dynamicMeshCoeffs_;


        // Face zone information (note: could pack these to only contain
        // used zones)

            //- Interpolation table. From faceZone to times.
            List<scalarField> times_;

            //- Interpolation table. From faceZone to displacements.
            List<vectorField> displacements_;

        // Range information.

            //- Per direction, per range the index of the lower
            //  faceZone
            FixedList<labelList, 3> rangeToZone_;

            //- Per direction, per range the points that are in it
            FixedList<labelListList, 3> rangeToPoints_;

            //- Per direction, per range the weight of the points relative
            //  to this and the next range.
            FixedList<List<scalarField>, 3> rangeToWeights_;


    // Private Member Functions

        //- Disallow default bitwise copy construct
        displacementInterpolationFvMotionSolver
        (
            const displacementInterpolationFvMotionSolver&
        );

        //- Disallow default bitwise assignment
        void operator=(const displacementInterpolationFvMotionSolver&);


public:

    //- Runtime type information
    TypeName("displacementInterpolation");


    // Constructors

        //- Construct from polyMesh and data stream
        displacementInterpolationFvMotionSolver
        (
            const polyMesh&,
            Istream& msDataUnused
        );


    // Destructor

        ~displacementInterpolationFvMotionSolver();


    // Member Functions

        //- Return point location obtained from the current motion field
        virtual tmp<pointField> curPoints() const;

        //- Solve for motion
        virtual void solve()
        {}
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
