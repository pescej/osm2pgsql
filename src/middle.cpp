/**
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * This file is part of osm2pgsql (https://osm2pgsql.org/).
 *
 * Copyright (C) 2006-2021 by the osm2pgsql developer community.
 * For a full list of authors see the git log.
 */

#include <cstdlib>
#include <cstring>

#include "logging.hpp"
#include "middle-db.hpp"
#include "middle-pgsql.hpp"
#include "middle-ram.hpp"
#include "middle.hpp"
#include "options.hpp"

std::shared_ptr<middle_t>
create_middle(options_t const &options, thread_pool_t *thread_pool)
{
    // hack to enable specific middle for testing
    char const *const middle_name = std::getenv("OSM2PGSQL_MIDDLE");
    if (middle_name) {
        log_debug("Middle set to '{}' from OSM2PGSQL_MIDDLE env var",
                  middle_name);
        if (std::strcmp(middle_name, "db") == 0) {
            return std::make_shared<middle_db_t>(&options, thread_pool);
        }
        if (std::strcmp(middle_name, "pgsql") == 0) {
            return std::make_shared<middle_pgsql_t>(&options, thread_pool);
        }
        if (std::strcmp(middle_name, "ram") == 0) {
            return std::make_shared<middle_ram_t>(&options, thread_pool);
        }
        if (std::strcmp(middle_name, "new") == 0) {
            if (options.slim) {
                return std::make_shared<middle_db_t>(&options, thread_pool);
            }
            return std::make_shared<middle_ram_t>(&options, thread_pool);
        }
        throw std::runtime_error{"Unknown middle '{}'"_format(middle_name)};
    }

    if (options.slim) {
        return std::make_shared<middle_pgsql_t>(&options, thread_pool);
    }

    return std::make_shared<middle_ram_t>(&options, thread_pool);
}

