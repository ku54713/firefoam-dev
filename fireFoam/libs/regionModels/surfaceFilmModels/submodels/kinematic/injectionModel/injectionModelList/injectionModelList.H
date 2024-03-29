/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2011 OpenCFD Ltd.
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
    Foam::injectionModelList

Description
    List container for film injection models

SourceFiles
    injectionModelList.C

\*---------------------------------------------------------------------------*/

#ifndef injectionModelList_H
#define injectionModelList_H

#include "PtrList.H"
#include "injectionModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace regionModels
{
namespace surfaceFilmModels
{

/*---------------------------------------------------------------------------*\
                    Class injectionModelList Declaration
\*---------------------------------------------------------------------------*/

class injectionModelList
:
    public PtrList<injectionModel>
{
private:

    // Private data

        //- Reference to the owner surface film model
        const surfaceFilmModel& owner_;

        //- Dictionary
        dictionary dict_;

        //- Cumulative mass injected total
        scalar injectedMassTotal_;


    // Private Member Functions

        //- Disallow default bitwise copy construct
        injectionModelList(const injectionModelList&);

        //- Disallow default bitwise assignment
        void operator=(const injectionModelList&);


public:

    // Constructors

        //- Construct null
        injectionModelList(const surfaceFilmModel& owner);

        //- Construct from type name, dictionary and surface film model
        injectionModelList
        (
            const surfaceFilmModel& owner,
            const dictionary& dict
        );


    //- Destructor
    virtual ~injectionModelList();


    // Member Functions

        // Evolution

            //- Correct
            virtual void correct
            (
                scalarField& availableMass,
                volScalarField& massToInject,
                volScalarField& diameterToInject
            );


        // I-O

            //- Provide some info
            void info(Ostream& os) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace surfaceFilmModels
} // End namespace regionModels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
