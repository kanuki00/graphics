import bpy
import json

dest_file = "/home/kanuki/Documents/GitRepos/graphics/tools/mesh_suzanne.json"
mesh = bpy.context.object.data
json_data = {}

for poly in mesh.polygons:
    if len(poly.vertices) > 3:
        raise Exception("Mesh not triangulated!")

with open(dest_file, "w") as file:
    json_data["indices"] = []
    for poly in mesh.polygons:
        for vertex in poly.vertices:
            json_data["indices"].append(vertex)

    json_data["vertices"] = []
    for vertex in mesh.vertices:
        json_data["vertices"].append([vertex.co.x, vertex.co.y, vertex.co.z])
        
    file.write(json.dumps(json_data, indent=4))
        