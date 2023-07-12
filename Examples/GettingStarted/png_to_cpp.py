from PIL import Image
import numpy as np

def bytes_to_cpp_array(data_type : str, variable_name : str, input_data : list[int]):
    
    accepted_data_types = ['uint8_t']
    if data_type not in accepted_data_types:
        return None


    cpp_string = str.format("const {} {}[] = ",data_type,variable_name)
    cpp_string += "{ \r\n"
    for n in range(len(input_data)):
        hex_string = (hex(input_data[n])).strip()
        cpp_string += str.format("{}, ",hex_string)

    cpp_string = cpp_string.removesuffix(", ") + "};"
    return cpp_string

def main():
    
    file_path = 'Graphics/128x64_splash_logo'
    extension = '.png'
    
    img = Image.open(file_path+extension)
    bytes = img.tobytes()
    
    byte_size = 8
    bitmap = []
    current_byte = 0
    for n in range(0, len(bytes), byte_size):
        byte_end = n+byte_size
        bits = bytes[n : byte_end]
        for bit in bits:
            current_byte = (current_byte << 1) | bit
            
        bitmap.append(current_byte)
        current_byte = 0
    
    print(bytes_to_cpp_array('uint8_t','rasmus',bitmap))
    print(len(bitmap))

main()




