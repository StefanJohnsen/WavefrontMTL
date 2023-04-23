# WavefrontMTL


Wavefront MTL Parser - C++ Class for Parsing Material Information

A header-only C++ wavefront material parser is a self-contained software component that can be included in C++ projects and is designed to parse and extract material properties from Wavefront Material Template Library (MTL) files. The parser operates solely on the material-related data in the MTL files, allowing for easy integration into C++ projects without the need for external dependencies. It can interpret and extract properties such as ambient color, diffuse color, specular color, shininess, transparency, and texture maps defined in the MTL file. The extracted material properties can then be used for tasks such as rendering realistic 3D objects in computer graphics applications.

The solution is self-contained in a single header file, making it easy to integrate into existing projects without the need for additional libraries or dependencies.

Key Features:

- Supports parsing of standard MTL parameters
- Supports parsing of Clara.io MTL parameters
- Supports parsing of DirectXMesh MTL parameters
- Retrieves header information and all materials in the MTL file
- Provides convenient access to material properties
- Robust and efficient parsing algorithm for handling large MTL files
- Suitable for integration into 3D graphics applications, game engines,
  and other computer graphics projects

#### Material Class

Certainly! Here's an example of how you can create a table in GitHub Markdown for the given `Material` struct:

| Member        | Type          | Description                                       |
|---------------|---------------|---------------------------------------------------|
| name          | Value\<std::string\> | Material name                                |
| Kd            | Color         | Color                                            |
| Ka            | Color         | Color Ambient                                     |
| Ks            | Color         | Color Specular                                    |
| Tf            | Color         | Color Transmission                               |
| Ns            | Value\<double\> | Shininess factor [0..1000]                       |
| map_Kd        | Texture       | Texture Diffuse                                   |
| map_Ka        | Texture       | Texture Ambient                                  |
| map_Ks        | Texture       | Texture Specular                                 |
| map_Ns        | Texture       | Texture Glossiness (Specular highlight component) |
| map_Pr        | Texture       | Texture Roughness                                 |
| map_Pm        | Texture       | Texture Metalness                                 |
| map_Ps        | Texture       | Texture Sheen                                     |
| map_d         | Texture       | Opacity Texture (alpha)                          |
| map_bump      | Texture       | Normal texture                                    |
| map_Po        | Texture       | Texture Occlusion                                 |
| sharpness     | Value\<double\> | Sharpness value [0..1000]                       |
| d             | Opacity       | Dissolve factor                                   |
| disp          | Texture       | Displacement map                                 |
| decal         | Texture       | Stencil decal                                    |
| bump          | Texture       | Normal texture, some use bump instead of map_bump |
| illum         | Value\<int\>    | Illumination [0..10]                            |
| Ni            | Value\<double\> | Optical density                                 |
| Tr            | Value\<double\> | Transparency                                    |
| refl          | Reflection    | Reflection map statements (Sphere/Cube)           |
| Ke            | Color         | Color Emissive (Physically Rendering/Clara.io)    |
| Pr            | Value\<double\> | Roughness factor (Physically Rendering/Clara.io) |
| Pm            | Value\<double\> | Metalness factor (Physically Rendering/Clara.io) |
| Ps            | Value\<double\> | Sheen factor (Physically Rendering/Clara.io)     |
| Pc            | Value\<double\> | Thickness factor (Physically Rendering/Clara.io) |
| Pcr           | Value\<double\> | Roughness factor (Physically Rendering/Clara.io) |
| aniso         | Value\<double\> | Anisotropy (Physically Rendering/Clara.io)       |
| anisor        | Value\<double\> | Anisotropy rotation (Physically Rendering/Clara.io) |
| map_Ke        | Texture       | Texture Emissive (Physically Rendering/Clara.io) |
| norm          | Texture       | Texture Normal (Physically Rendering/Clara.io)   |
| map_RMA       | Texture       | Texture RMA (DirectXMesh/Microsoft's DirectX engine) |
| map_ORM       | Texture       | Texture ORM (DirectXMesh/Microsoft's DirectX engine) |

You can copy and paste the above table into a GitHub Markdown file (e.g., README.md) in your repository to create a table that displays the members, types, and descriptions of the `Material` struct in a tabular format.


## License
WavefrontMTL is licensed under MIT license.

