from PIL import Image
import binascii
import io

if __name__ == "__main__":
    hex_string = "insert hex string here"
    binary_data = binascii.unhexlify(hex_string)
    image_data = io.BytesIO(binary_data)
    image = Image.open(image_data)
    image.save('output_image.jpg', 'JPEG')
