# 42cursus_04_miniRT

|<img src="https://user-images.githubusercontent.com/52701529/184656361-80d7e19d-9211-44ba-92d7-6566a8da2d50.png" width=100%>|![image](https://user-images.githubusercontent.com/52701529/184659380-5e98cf41-9ca5-4161-bfd9-c0e7fc8b38d9.png)|
|---|---|


study about ray tracing
- https://velog.io/@zhy2on/%EB%AF%B8%EB%8B%88%EC%95%8C%ED%8B%B0-ldvma6zf

## rt file format
### common ground

| Type |  mean  |    |    |    |
|:----:|:----:|:----:|:----:|:----:|
| ``A`` | ambient light | - | ``ratio`` | ``color`` |
| ``L`` | light | ``position`` | ``ratio`` | ``color`` |
| ``C`` | camera | ``position`` | ``normal vector`` | ``fov`` |
| ``#`` | comment | - | - | - |

### mandatory
| Figure | position | normal vector | radius | height | color |
|:----:|:----:|:----:|:----:|:----:|:----:|
| ``pl`` | ✅ | ✅ | - | - | 🎨 |
| ``sp`` | ✅ | - | ✅ | - | 🎨 |
| ``cy`` | ✅ | ✅ | ✅ | ✅ | 🎨 |

### bonus
| Type |  mean  |  |  |  |
|:----:|:----:|:----:|:----:|:----:|
| ``R`` | resolution | width | height | - | - |
| ``tx`` | texture | texture id | image map file path | normal map file path |

| Figure | position | normal vector | radius / theta | height | specular power | checkerboard w,h | color | texture |
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|
| ``pl`` | ✅ | ✅ | - | - | 🪞 | ♟ | 🎨 | tx id |
| ``sp`` | ✅ | - | ``R`` | - | 🪞 | ♟ | 🎨 | tx id |
| ``cy`` | ✅ | ✅ | ``R`` | ✅ | 🪞 | ♟ | 🎨 | tx id |
| ``con`` | ✅ | ✅ | ``Th`` | ✅ | 🪞 | ♟ | 🎨 | tx id |

### example
```
A  0.5   255,255,255
L  10,1,5   0.4   255,255,255
C  19.5,0,10   0,1,-1   40
# C  19.4,10,10   0,0,-1   40

# | position | normal vector | radius | height | color |
pl 0,0,0         0,0,1                           255,255,255
sp 18.8,10,0.6                  1.2              255,125,0
sp 20,10,0.6                    1.2              123,200,93
sp 21.2,10,0.6                  1.2              238,250,110
cy 17.6,10,1.3   0,0,-1         1.2      1.3     255,150,200
```

```
# bonus ex
R  800 800
A  0.5   255,255,255
L  10,1,5   0.4   255,255,255
C  20,0,10   0,1,-1   40
C  20,10,5   0,0,-1   80

tx	earth	scenes/textures/earth_no_clouds_8k.xpm		scenes/textures/earth_normal.xpm
tx	rock	scenes/textures/rock.xpm		scenes/textures/rock_normal.xpm

# |   position  | normal vector | r / th | height | spec power | checker w,h |    color     | texture |
pl   0,0,0          0,0,1                             100           0,0        255,255,255
sp   18.8,10,0.6                   1.2                100           0,0        255,125,0
sp   20,10,0.6                     1.2                100           0,0        123,200,93
sp   21.2,10,0.6                   1.2                100           0,0        238,250,110
cy   17.6,10,1.3    0,0,-1         1.2      1.3       100           0,0        255,150,200
con  22.3,10,1.3    0,0,-1         30       1.3       100           0,0        0,176,240
```

 
