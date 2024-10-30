import re
import xml.etree.ElementTree as ET

def parse_layer_data(data_text):
    # Parse CSV data, returning a 2D list of integers for easier processing
    rows = []
    for line in data_text.strip().splitlines():
        cols = []
        for tile in line.split(','):
            if tile not in [',', '']:
                cols.append(int(tile))
        rows.append(cols)
    return rows

def get_layer_position_data(layer_data):
    # Extract non-zero tiles with their position for enemies and objects
    position_data = []
    for y, row in enumerate(layer_data):
        for x, tile in enumerate(row):
            if tile != 0:  # Assuming 0 means empty space
                position_data.append((tile, x, y))
    return position_data

def modify_head(file_path, output_path):
    # Parse the XML structure
    tree = ET.parse(file_path)
    root = tree.getroot()
    
    # Extract map attributes for header
    width = root.attrib['width']
    height = root.attrib['height']
    tilewidth = root.attrib['tilewidth']
    tileheight = root.attrib['tileheight']
    
    for tileset in tree.findall('tileset'):
        if 'interactives' in tileset.attrib['source']:
            objects_start_idx = int(tileset.attrib['firstgid'])
        if 'enemies' in tileset.attrib['source']:
            enemies_start_idx = int(tileset.attrib['firstgid'])
        if '1' == tileset.attrib['firstgid']:
            file = tileset.attrib['source'][3:].replace('.tsx', '.png')

    tile_sheet_size = input("How many tiles in tilesheet (x y)? ")

    # Write the new header
    new_header = f'''TILEMAP
{width} {height}                           -- Size of tile map in tiles
{tilewidth} {tileheight}                   -- Tile size & block size
{file}                                     -- Tilesheet
{tile_sheet_size}                          -- Number of tiles in tilesheet
'''

    # Open output file and write header
    with open(output_path, 'w', encoding='utf-8') as output_file:
        output_file.write(new_header)
        
        # Process each layer in the map
        for layer in root.findall('layer'):
            layer_name = layer.attrib['name']
            data_element = layer.find('data')
            
            # Decode CSV data for the layer
            layer_data = parse_layer_data(data_element.text)
            
            # Separate handling based on layer type
            if layer_name == "Map" or layer_name == "Decorations":
                output_file.write(f"\n{layer_name.upper()}\n")
                for row in layer_data:
                    output_file.write(" ".join(map(str, row)) + "\n")
            elif layer_name == "Enemies" or layer_name == "Objects":
                output_file.write(f"\n{layer_name.upper()}\n")
                position_data = get_layer_position_data(layer_data)
                for tile, x, y in position_data:
                    tile -= enemies_start_idx if layer_name == "Enemies" else objects_start_idx
                    output_file.write(f"{tile} {x} {y}\n")
                    
    print(f"File modified and saved to {output_path}")

# Usage
map_list = ['./CastleOfIllusions/CastleOfIllusions/levels/chocolate_map.tmx']
for i in map_list:
    modify_head(i, i.replace('.tmx', '_prueba.txt'))
