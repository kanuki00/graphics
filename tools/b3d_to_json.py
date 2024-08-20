bl_info = {
    "name": "Blender 3D model to json format",
    "blender": (4, 2, 0),
    "category": "Object"
}

import bpy
import json
from bpy.props import StringProperty


class MeshToJson(bpy.types.Operator):
    bl_idname = "object.mesh_to_json"
    bl_label = "Mesh to json"
    
    dest_file: StringProperty(
            name="Destination File", 
            default=""
        )
        
    # creates popup widow, so that user can set dest_file
    def invoke(self, context, event):
        wm = context.window_manager
        return wm.invoke_props_dialog(self)
        
    def draw(self, context):
        self.layout.prop(self, "dest_file", text="File to write json data to")
    
    def execute(self, context):
        mesh = bpy.context.object.data
        json_data = {}

        for poly in mesh.polygons:
            if len(poly.vertices) > 3:
                raise Exception("Mesh not triangulated!")

        with open(self.dest_file, "w") as file:
            json_data["indices"] = []
            for poly in mesh.polygons:
                for vertex in poly.vertices:
                    json_data["indices"].append(vertex)

            json_data["vertices"] = []
            for vertex in mesh.vertices:
                json_data["vertices"].append([vertex.co.x, vertex.co.y, vertex.co.z])
                
            file.write(json.dumps(json_data, indent=4))
        return {"FINISHED"}



class VIEW3D_PT_mesh_to_json(bpy.types.Panel):
    bl_space_type = "VIEW_3D"
    bl_region_type = "UI"
    
    bl_category = "Mesh to json"
    bl_label = "Mesh to json"
    
    def draw(self, context):
        row = self.layout.row()
        row.operator("object.mesh_to_json", text="Mesh to json")
        
    
def register():
    bpy.utils.register_class(MeshToJson)
    bpy.utils.register_class(VIEW3D_PT_mesh_to_json)
    
    
def unregister():
    bpy.utils.unregister_class(MeshToJson)
    
    
if __name__ == "__main__":
    register()
    