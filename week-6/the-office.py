# import python image library
from PIL import Image
# import a face recognition library
import face_recognition

# open the office image
image = face_recognition.load_image_file("office.jpg")

# a list of all of the faces in the image using detection library
face_locations = face_recognition.face_locations(image)

# for each face detected in the image
for face_location in face_locations:
    # get the coordinates of the face
    top,right,bottom,left = face_location
    # show that face alone if it is detected (of the scranton strangler)
    face_image = image[top:bottom, left:right]
    pil_image = Image.fromarray(face_image)
    pil_image.show()