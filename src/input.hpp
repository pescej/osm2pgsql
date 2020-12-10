#ifndef OSM2PGSQL_INPUT_HPP
#define OSM2PGSQL_INPUT_HPP

/**
 * \file
 *
 * This file is part of osm2pgsql (https://github.com/openstreetmap/osm2pgsql).
 *
 * It contains the functions reading and checking the input data.
 */

#include <vector>

#include <osmium/fwd.hpp>
#include <osmium/io/file.hpp>

#include "osmtypes.hpp"

class osmdata_t;
class progress_display_t;

struct type_id_version
{
    osmium::item_type type;
    osmid_t id;
    osmium::object_version_type version;
};

/**
 * Compare two tuples (type, id, version) throw a descriptive error if either
 * the curr id is negative or if the data is not ordered.
 */
type_id_version check_input(type_id_version const &last, type_id_version curr);

type_id_version check_input(type_id_version const &last,
                            osmium::OSMObject const &object);

/**
 * Prepare input file(s). Does format checks as far as this is possible
 * without actually opening the files.
 */
std::vector<osmium::io::File>
prepare_input_files(std::vector<std::string> const &input_files,
                    std::string const &input_format, bool append);

/**
 * Process the specified OSM files (stage 1a).
 */
void process_files(std::vector<osmium::io::File> const &files,
                   osmdata_t &osmdata, bool append, bool show_progress);

#endif // OSM2PGSQL_INPUT_HPP
