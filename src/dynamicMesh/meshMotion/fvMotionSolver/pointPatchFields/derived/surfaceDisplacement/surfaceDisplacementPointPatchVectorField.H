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
    surfaceDisplacementPointPatchVectorField

Description
    Displacement fixed by projection onto triSurface.
    Use in a displacement fvMotionSolver
    as a bc on the pointDisplacement field.

    Calculates the projection onto the surface according
    to the projectMode
    - NEAREST : nearest
    - POINTNORMAL : intersection with point normal
    - FIXEDNORMAL : intersection with fixed vector

    This displacement is then clipped with the specified velocity * deltaT.

    Optionally (intersection only) removes a component ("wedgePlane") to
    stay in 2D.

    Needs:
    - geometry : dictionary with searchableSurfaces. (usually
      triSurfaceMeshes in constant/triSurface)
    - projectMode : see above
    - projectDirection : if projectMode = fixedNormal
    - wedgePlane : -1 or component to knock out of intersection normal
    - frozenPointsZone : empty or name of pointZone containing points
                         that do not move

SourceFiles
    surfaceDisplacementPointPatchVectorField.C

\*---------------------------------------------------------------------------*/

#ifndef surfaceDisplacementPointPatchVectorField_H
#define surfaceDisplacementPointPatchVectorField_H

#include "pointPatchFields.H"
#include "fixedValuePointPatchFields.H"
#include "searchableSurfaces.H"
#include "Switch.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
          Class surfaceDisplacementPointPatchVectorField Declaration
\*---------------------------------------------------------------------------*/

class surfaceDisplacementPointPatchVectorField
:
    public FixedValuePointPatchField
    <
        pointPatchField,
        pointMesh,
        pointPatch,
        DummyMatrix,
        vector
    >
{

public:

    // Public data types

        enum projectMode
        {
            NEAREST,
            POINTNORMAL,
            FIXEDNORMAL
        };

private:

    // Private data

        //- project mode names
        static const NamedEnum<projectMode, 3> projectModeNames_;

        //- Maximum velocity
        const vector velocity_;

        //- names of surfaces
        const dictionary surfacesDict_;

        //- How to project/project onto surface
        const projectMode projectMode_;

        //- direction to project
        const vector projectDir_;

        //- plane for 2D wedge case or -1.
        const label wedgePlane_;

        //- pointZone with frozen points
        const word frozenPointsZone_;

        //- Demand driven: surface to project
        mutable autoPtr<searchableSurfaces> surfacesPtr_;


    // Private Member Functions

        //- Calculate displacement (w.r.t. points0()) to project onto surface
        void calcProjection(vectorField& displacement) const;


        //- Disallow default bitwise assignment
        void operator=(const surfaceDisplacementPointPatchVectorField&);

public:

    //- Runtime type information
    TypeName("surfaceDisplacement");


    // Constructors

        //- Construct from patch and internal field
        surfaceDisplacementPointPatchVectorField
        (
            const pointPatch&,
            const DimensionedField<vector, pointMesh>&
        );

        //- Construct from patch, internal field and dictionary
        surfaceDisplacementPointPatchVectorField
        (
            const pointPatch&,
            const DimensionedField<vector, pointMesh>&,
            const dictionary&
        );

        //- Construct by mapping given patchField<vector> onto a new patch
        surfaceDisplacementPointPatchVectorField
        (
            const surfaceDisplacementPointPatchVectorField&,
            const pointPatch&,
            const DimensionedField<vector, pointMesh>&,
            const PointPatchFieldMapper&
        );

        //- Construct as copy
        surfaceDisplacementPointPatchVectorField
        (
            const surfaceDisplacementPointPatchVectorField&
        );

        //- Construct and return a clone
        virtual autoPtr<pointPatchVectorField> clone() const
        {
            return autoPtr<pointPatchVectorField>
            (
                new surfaceDisplacementPointPatchVectorField
                (
                    *this
                )
            );
        }

        //- Construct as copy setting internal field reference
        surfaceDisplacementPointPatchVectorField
        (
            const surfaceDisplacementPointPatchVectorField&,
            const DimensionedField<vector, pointMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual autoPtr<pointPatchVectorField> clone
        (
            const DimensionedField<vector, pointMesh>& iF
        ) const
        {
            return autoPtr<pointPatchVectorField>
            (
                new surfaceDisplacementPointPatchVectorField
                (
                    *this,
                    iF
                )
            );
        }

    // Member Functions

        //- Surface to follow. Demand loads surfaceNames.
        const searchableSurfaces& surfaces() const;

        //- Update the coefficients associated with the patch field
        virtual void updateCoeffs();

        //- Write
        virtual void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
