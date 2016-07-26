---
layout: internal
---

## Meshing

# Move Dynamic Mesh


`moveDynamicMesh` is the default meshing utility.

It starts with a mesh generated by `blockMesh` and iteratively refines the mesh according to the DEM surface and other information specified in `0/pointDisplacement`. The solver to use for `cellDisplacement` is specified in `system/fvSolution`. We are using the `displacementSBRStress` solver with `quadratic inverseDistance` diffusivity. The displacement `velocity` * `deltaT` (specified in `0/pointDisplacement`) must be less than the distance between the near-surface layers in the block mesh, otherwise points may move too quickly toward the surface, causing some cells to get turned inside-out. `deltaT` is set to 1.0 in `controlDict`.

Relevant files:

* `constant/polyMesh/blockMeshDict`
* `0/pointDisplacement`
* `constant/dynamicMeshDict`
* `system/fvSolution`
* `system/controlDict`


# Example


## blockMeshDict


    /*---------------------------------------------------------------------------*\
    | =========                 |                                                 |
    | \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
    |  \\    /   O peration     | Version:  2.2.0                                 |
    |   \\  /    A nd           | Web:      http://www.openfoam.org               |
    |    \\/     M anipulation  |                                                 |
    \*---------------------------------------------------------------------------*/

    FoamFile
    {
        version         2.0;
        format          ascii;

        root            "";
        case            "";
        instance        "";
        local           "";

        class           dictionary;
        object          blockMeshDict;
    }

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


    convertToMeters 1;

    vertices
    (
        (431525.59453113563  5291447.3730044467  2362.8000000000002)
        (444405.27855891304  5291447.3730044467  2362.8000000000002)
        (444405.27855891304  5302993.6309211124  2362.8000000000002)
        (431525.59453113563  5302993.6309211124  2362.8000000000002)
        (431525.59453113563  5291447.3730044467  7055.5)
        (444405.27855891304  5291447.3730044467  7055.5)
        (444405.27855891304  5302993.6309211124  7055.5)
        (431525.59453113563  5302993.6309211124  7055.5)
    );

    blocks
    (
        hex (0 1 2 3 4 5 6 7) (145 130 52) simpleGrading (1.0 1.0 1)
    );

    edges
    (
    );

    patches
    (

        patch north_face
        (
            (3 7 6 2)
        )
        patch west_face
        (
            (0 4 7 3)
        )
        patch east_face
        (
            (2 6 5 1)
        )
        patch south_face
        (
            (1 5 4 0)
        )
        wall minZ
        (
            (0 3 2 1)
        )
        patch maxZ
        (
            (4 5 6 7)
        )
    );

    mergePatchPairs
    (
    );


    // ************************************************************************* //