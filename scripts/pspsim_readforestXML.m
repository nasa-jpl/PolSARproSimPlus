function data = pspsim_readforestXML(filename)

%read in the xml file
xDoc = xmlread(filename);

%read in the forest
forest = xDoc.getElementsByTagName('tree');

%iterate over each tree in forest
for ii=0:forest.getLength-1
    %get a tree
    tree = forest.item(ii);
    
    %read all attributes for the tree
    rawdata.species{ii+1}       = tree.getElementsByTagName('species').item(0).getFirstChild.getData;
    rawdata.x_location{ii+1}    = tree.getElementsByTagName('x_location').item(0).getFirstChild.getData;
    rawdata.y_location{ii+1}    = tree.getElementsByTagName('y_location').item(0).getFirstChild.getData;
    rawdata.tree_height{ii+1}   = tree.getElementsByTagName('tree_height').item(0).getFirstChild.getData;
    rawdata.canopy_radius{ii+1} = tree.getElementsByTagName('canopy_radius').item(0).getFirstChild.getData;
    rawdata.canopy_depth{ii+1}  = tree.getElementsByTagName('canopy_depth').item(0).getFirstChild.getData;
    rawdata.dry_depth{ii+1}     = tree.getElementsByTagName('dry_depth').item(0).getFirstChild.getData;
    rawdata.stem_diameter{ii+1} = tree.getElementsByTagName('stem_diameter').item(0).getFirstChild.getData;
end
data.species        = rawdata.species;
data.x_location     = cellfun(@(x) x(:),cellfun(@(x) str2double(char(x)), rawdata.x_location, 'UniformOutput', false));
data.y_location     = cellfun(@(x) x(:),cellfun(@(x) str2double(char(x)), rawdata.y_location, 'UniformOutput', false));
data.tree_height    = cellfun(@(x) x(:),cellfun(@(x) str2double(char(x)), rawdata.tree_height, 'UniformOutput', false));
data.canopy_radius  = cellfun(@(x) x(:),cellfun(@(x) str2double(char(x)), rawdata.canopy_radius, 'UniformOutput', false));
data.canopy_depth   = cellfun(@(x) x(:),cellfun(@(x) str2double(char(x)), rawdata.canopy_depth, 'UniformOutput', false));
data.dry_depth      = cellfun(@(x) x(:),cellfun(@(x) str2double(char(x)), rawdata.dry_depth, 'UniformOutput', false));
data.stem_diameter  = cellfun(@(x) x(:),cellfun(@(x) str2double(char(x)), rawdata.stem_diameter, 'UniformOutput', false));
