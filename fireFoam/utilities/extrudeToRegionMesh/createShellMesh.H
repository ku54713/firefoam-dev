/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 1991-2010 OpenCFD Ltd.
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
    Foam::createShellMesh

Description
    Creates mesh by extruding a patch.

SourceFiles
    createShellMesh.C

    Extrudes into thickness direction.
    - bottom faces originate from reversed original faces (have turning index)
    - top faces originate from original faces (no turning index)

\*---------------------------------------------------------------------------*/

#ifndef createShellMesh_H
#define createShellMesh_H

#include "primitiveFacePatch.H"
#include "PackedBoolList.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of classes
class mapPolyMesh;
class polyTopoChange;

/*---------------------------------------------------------------------------*\
                           Class createShellMesh Declaration
\*---------------------------------------------------------------------------*/

class createShellMesh
{
    // Private data

        //- Reference to patch to extrude
        const primitiveFacePatch& patch_;

        //- Per point on face the region
        const faceList& pointRegions_;

        //- From region to original patch point
        const labelList& regionPoints_;


        labelList cellToFaceMap_;

        labelList faceToFaceMap_;

        labelList faceToEdgeMap_;

        labelList pointToPointMap_;


    // Private Member Functions

        //- Disallow default bitwise copy construct
        createShellMesh(const createShellMesh&);

        //- Disallow default bitwise assignment
        void operator=(const createShellMesh&);


public:

    //- Runtime type information
    ClassName("createShellMesh");


    // Constructors

        //- Construct from mesh.
        createShellMesh
        (
            const primitiveFacePatch& patch,
            const faceList& pointRegions,
            const labelList& regionPoints
        );


    // Member Functions


        // Access

            //- From region cell to patch face. Consecutively added so
            //  cell at layerI is at patchFaceI*nLayers+layerI
            const labelList& cellToFaceMap() const
            {
                return cellToFaceMap_;
            }

            //- From region face to patch face. Contains turning index:
            //      > 0 : face in same orientation as patch face. face will
            //            be in top patch
            //      < 0 : face in opposite orientation as patch face. face will
            //            be in bottom patch
            //      = 0 : for all side and internal faces
            const labelList& faceToFaceMap() const
            {
                return faceToFaceMap_;
            }

            //- From region side-face to patch edge. -1 for non-edge faces.
            const labelList& faceToEdgeMap() const
            {
                return faceToEdgeMap_;
            }

            //- From region point to patch point.
            const labelList& pointToPointMap() const
            {
                return pointToPointMap_;
            }


        // Other

            //- Helper: calculate point regions
            static void calcPointRegions
            (
                const primitiveFacePatch& patch,
                const PackedBoolList& nonManifoldEdge,
                faceList& pointRegions,
                labelList& regionPoints
            );

            //- Play commands into polyTopoChange to create layer mesh.
            void setRefinement
            (
                const pointField& firstLayerThickness,
                const scalar expansionRatio,
                const label nLayers,
                const labelList& topPatchID,
                const labelList& bottomPatchID,
                const labelListList& extrudeEdgePatches,
                polyTopoChange& meshMod
            );

            //- Update any locally stored mesh information.
            void updateMesh(const mapPolyMesh&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
