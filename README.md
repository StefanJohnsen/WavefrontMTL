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

## Material Class

| Type               | Variable                          | Description
|--------------------------------------------------------------------------------------------------------------------------------|
| string             | name                             | Material name														                               |
| Color              | Kd                               | Color																                                   |
| Color              | Ka                               | Color Ambient														                               |
| Color              | Ks                               | Color Specular														                             |
| Color              | Tf                               | Color Transmission													                           |
| Value<double>      | Ns                               | Shininess  factor [0..1000]											                       |
| Texture            | map_Kd                           | Texture Diffuse														                             |
| Texture            | map_Ka                           | Texture Ambient														                             |
| Texture            | map_Ks                           | Texture Specular														                           |
| Texture            | map_Ns                           | Texture Glossiness			(Specular highlight component)			           |
| Texture            | map_Pr                           | Texture Roughness													                             |
| Texture            | map_Pm                           | Texture Metalness													                             |
| Texture            | map_Ps                           | Texture Sheen														                               |
| Texture            | map_d                            | Opacity Texture (alpha)												                         |
| Texture            | map_bump                         | Normal texture														                             |
| Texture            | map_Po                           | Texture Occlusion													                             |
| Value<double>      | sharpness                        | Sharpness value [0..1000]											                         |
| Opacity            | d                                | Dissolve factor														                             |
| Texture            | disp                             | Displacement map														                           |
| Texture            | decal                            | Stencil decal														                               |
| Texture            | bump                             | Normal texture, some use bump instead of map_bump					             |
| Value<int>         | illum                            | Illumination [0..10]													                         |
| Value<double>      | Ni                               | Optical density														                             |
| Value<double>      | Tr                               | Transparency															                             |
| Reflection         | refl                             | Reflection map statements	(Sphere/Cube)							                   |
| Color              | Ke                               | Color Emissive				  (Physically Rendering/Clara.io)			           |
| Value<double>      | Pr                               | Roughness factor				(Physically Rendering/Clara.io)			           |
| Value<double>      | Pm                               | Metalness factor				(Physically Rendering/Clara.io)			           |
| Value<double>      | Ps                               | Sheen factor					  (Physically Rendering/Clara.io)			           |
| Value<double>      | Pc                               | Thickness factor				(Physically Rendering/Clara.io)			           |
| Value<double>      | Pcr                              | Roughness factor				(Physically Rendering/Clara.io)			           |
| Value<double>      | aniso                            | Anisotropy					    (Physically Rendering/Clara.io)			           |
| Value<double>      | anisor                           | Anisotropy rotation			(Physically Rendering/Clara.io)			           |
| Texture            | map_Ke                           | Texture Emissive				(Physically Rendering/Clara.io)			           |
| Texture            | norm                             | Texture Normal				  (Physically Rendering/Clara.io)			           |
| Texture            | map_RMA                          | Texture RMA					    (DirectXMesh/Microsoft's DirectX engine)       |
| Texture            | map_ORM                          | Texture ORM					    (DirectXMesh/Microsoft's DirectX engine)       |


## License
WavefrontMTL is licensed under MIT license.

