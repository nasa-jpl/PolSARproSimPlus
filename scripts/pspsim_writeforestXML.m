function pspsim_writeforestXML(data, filename, biome)
% reading from the tabbed forest file and writing to the XML forest file

%some basic checks
assert(isfield(data, 'species'), 'species field needs to exist in data structure');
assert(isfield(data, 'x_location'), 'x_location field needs to exist in data structure');
assert(isfield(data, 'y_location'), 'y_location field needs to exist in data structure');
assert(isfield(data, 'tree_height'), 'tree_height field needs to exist in data structure');
assert(isfield(data, 'canopy_radius'), 'canopy_radius field needs to exist in data structure');
assert(isfield(data, 'canopy_depth'), 'canopy_depth field needs to exist in data structure');
assert(isfield(data, 'dry_depth'), 'dry_depth field needs to exist in data structure');
assert(isfield(data, 'stem_diameter'), 'stem_diameter field needs to exist in data structure');

if(~exist('biome', 'var'))
    biome = 'unkown';
end

%open file
fid=fopen(filename, 'wt');

%write preamble
fprintf(fid, '<?xml version="1.0" encoding="ISO-8859-15"?>\n');
fprintf(fid, '<?xml-stylesheet type="text/xsl" href="forest.xsl"?>\n');

%write forest tag
fprintf(fid, '<forest>\n');

%write the meta tag
trees   = length(data.species);
area    = pi*(max(max(abs(data.x_location),abs(data.y_location))))^2/100/100;
fprintf(fid, '\t<meta>\n');
fprintf(fid, '\t\t<num_trees\tunits="none">\t%9d\t</num_trees>\t\t<!-- The total number of trees in this file\t\t\t-->\n', trees);
fprintf(fid, '\t\t<biome\t\tunits="none">\t%9s\t</biome>\t\t<!-- The biome this forest belongs to\t\t\t\t-->\n', biome);
fprintf(fid, '\t\t<area\t\tunits="ha">\t%9.4f\t</area>\t\t\t<!-- The total area of the forest \t\t\t\t-->\n', area);
fprintf(fid, '\t</meta>\n');

%write the trees
for ii=1:length(data.species)
    fprintf(fid, '\t<tree>\n');
    fprintf(fid, '\t\t<species\tunits="none">\t%9s\t</species>\t\t<!-- (see allometry file)\t\t\t\t\t-->\n', strtrim(char(data.species{ii})));
    fprintf(fid, '\t\t<x_location\tunits="meters">\t%9.4f\t</x_location>\t\t<!-- X-axis location of tree, scene center is 0.00\t\t-->\n', data.x_location(ii));
    fprintf(fid, '\t\t<y_location\tunits="meters">\t%9.4f\t</y_location>\t\t<!-- Y-axis location of tree, scene center is 0.00\t\t-->\n', data.y_location(ii));
    fprintf(fid, '\t\t<tree_height\tunits="meters">\t%9.4f\t</tree_height>\t\t<!-- Vertical extent from tree base to canopy top\t\t-->\n', data.tree_height(ii));
    fprintf(fid, '\t\t<canopy_radius\tunits="meters">\t%9.4f\t</canopy_radius>\t<!-- The largest horizontal radius of the canopy\t\t-->\n', data.canopy_radius(ii));
    fprintf(fid, '\t\t<canopy_depth\tunits="meters">\t%9.4f\t</canopy_depth>\t\t<!-- The depth of the live part of the canopy\t\t\t-->\n', data.canopy_depth(ii));
    fprintf(fid, '\t\t<dry_depth\tunits="meters">\t%9.4f\t</dry_depth>\t\t<!-- The depth of the dry part of the canopy\t\t\t-->\n', data.dry_depth(ii));
    fprintf(fid, '\t\t<stem_diameter\tunits="meters">\t%9.4f\t</stem_diameter>\t<!-- Diameter of trunk at breast height (dbh)\t\t\t-->\n', data.stem_diameter(ii));
    fprintf(fid, '\t</tree>\n');
end
fprintf(fid, '</forest>\n');

fclose(fid);