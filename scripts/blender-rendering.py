import bpy
from os import system
import os.path
import math


# 1) Clear the terminal

system('clear')



# 1) Remove the current room OBJ model

print('### Removing the active room')

#object_to_delete = bpy.data.objects['room-demo-ACTIVE.002']
objs = [obj for obj in bpy.context.scene.objects if obj.name.startswith("room-demo-ACTIVE")]

for obj in objs:
    bpy.data.objects.remove(obj, do_unlink=True)




# 2) Load the replacement room OBJ model

print('### Loading the new active room')

file_loc = '/Users/markoates/Desktop/room-demo-ACTIVE.obj'

imported_object = bpy.ops.import_scene.obj(filepath=file_loc)
obj_object = bpy.context.selected_objects[0]
print('Imported object named: ', obj_object.name)




# 3) Position the camera and capture the renders

print('### Positioning the camera and capturing renders')

natural_view_height = 1.2
room_x_spacing = 12.0

x_rot = 89.2
y_rot = 0
z_rot = 0

rotated_x_offset = 1.86
rotated_y_offset = 0.2
rotated_z_rot_offset = 11.8

F2 = 10.0
back_offset = 13;


camera_locations = {
    'front_porch':              [(room_x_spacing * -1-rotated_x_offset, -6.6+rotated_y_offset, natural_view_height), (x_rot, y_rot, z_rot-rotated_z_rot_offset)],
    'front_hallway':            [(room_x_spacing * 0,  -6.6, natural_view_height), (x_rot, y_rot, z_rot)],
    'main_hallway':             [(room_x_spacing * 1,  -6.6, natural_view_height), (x_rot, y_rot, z_rot)],
    'first_floor_storage_room': [(room_x_spacing * 2,  -6.6, natural_view_height), (x_rot, y_rot, z_rot)],
    'back_porch':               [(room_x_spacing * 3+rotated_x_offset,  -6.6+rotated_y_offset, natural_view_height), (x_rot, y_rot, z_rot+rotated_z_rot_offset)],


    'upstairs_utility_room':    [(room_x_spacing * -1,  -6.6, F2+natural_view_height), (x_rot, y_rot, z_rot)],
    'upstairs_stairwell':       [(room_x_spacing * 0,  -6.6, F2+natural_view_height), (x_rot, y_rot, z_rot)],
    'upstairs_living_hallway':  [(room_x_spacing * 1,  -6.6, F2+natural_view_height), (x_rot, y_rot, z_rot)],
    'master_entry':             [(room_x_spacing * 2,  -6.6, F2+natural_view_height), (x_rot, y_rot, z_rot)],

    'master_bedroom':           [(room_x_spacing * 2,  -6.6+back_offset, F2+natural_view_height), (x_rot, y_rot, z_rot)],
    'master_balcony':           [(room_x_spacing * 3+rotated_x_offset,  -6.6+back_offset+rotated_y_offset, F2+natural_view_height), (x_rot, y_rot, z_rot+rotated_z_rot_offset)],

    'attic':                    [(room_x_spacing * -1,  -6.6+back_offset, F2+natural_view_height), (x_rot, y_rot, z_rot)],
    'girls_room':               [(room_x_spacing * 0,  -6.6+back_offset, F2+natural_view_height), (x_rot, y_rot, z_rot)],
    'boys_room':                [(room_x_spacing * 1,  -6.6+back_offset+4, F2+natural_view_height), (x_rot, y_rot, z_rot)],

    'back_porch_detail':         [(room_x_spacing * 3+rotated_x_offset+4,  -6.6+rotated_y_offset+8, natural_view_height), (x_rot, y_rot, z_rot+rotated_z_rot_offset*6)],
    'basement':                  [(room_x_spacing * 2,  -6.6, natural_view_height-7), (x_rot, y_rot, z_rot)],

}


#    'attic'
#    'boys_room'
#    'girls_room'
#    'back_porch_detail'
#    'basement'


# Scene variables
scn = bpy.context.scene
cam = scn.camera
pi = math.pi
# output_path = "/Users/markoates/Desktop/output_renders/" #scn.render.filepath
output_path = "/Users/markoates/Repos/TheWeepingHouse/bin/programs/data/bitmaps/rooms/" #scn.render.filepath

# Iterate through the dict, set the locations and render
for k, v in camera_locations.items():
    # Set the location
    cam.location = v[0]
    # Set the rotation
    cam.rotation_mode = 'XYZ'
    cam.rotation_euler[0] = v[1][0] * (pi / 180.0);
    cam.rotation_euler[1] = v[1][1] * (pi / 180.0);
    cam.rotation_euler[2] = v[1][2] * (pi / 180.0);
    # Assemble the path (.jpg is a placeholder)
    scn.render.filepath = os.path.join(output_path, "room_{}.jpg".format(k))
    # Call the render operator
    bpy.ops.render.render(write_still=True)

# Reset the output path to "Users/markoates/Desktop/output_renders/"
bpy.context.scene.render.filepath = output_path

