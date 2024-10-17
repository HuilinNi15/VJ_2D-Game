import re

def modify_head(file_path, output_path):
    # Read the original file
    with open(file_path, 'r', encoding='utf-8') as file:
        lines = file.readlines()

    # Extract values from the XML header
    xml_header = "".join(lines[:10])  # Assuming the header is within the first 10 lines

    # Use regular expressions to find the needed values
    width = re.search(r'width="(\d+)"', xml_header).group(1)
    height = re.search(r'height="(\d+)"', xml_header).group(1)
    tilewidth = re.search(r'tilewidth="(\d+)"', xml_header).group(1)
    tileheight = re.search(r'tileheight="(\d+)"', xml_header).group(1)

    # Prepare the new header with the extracted values
    new_header = f'''TILEMAP
{width} {height}                           -- Size of tile map in tiles
{tilewidth} {tileheight}                   -- Tile size & block size
images/tiles.png                           -- Tilesheet
16 8                                       -- Number of tiles in tilesheet
'''

    # Filter lines that don't start with '<' and replace commas with spaces in the data lines
    filtered_lines = []
    for line in lines:
        if not line.strip().startswith('<'):
            # Replace commas with spaces
            filtered_lines.append(line.replace(',', ' '))

    # Write the new file with the modified header
    with open(output_path, 'w', encoding='utf-8') as output_file:
        output_file.write(new_header)  # Write the new header
        output_file.writelines(filtered_lines)  # Write the rest of the file content


map_list = ['chocolate_map.txt', 'forest_practice_map.txt']
for i in map_list:
    modify_head(i, i)
    print(f"File modified and saved to {i}")
