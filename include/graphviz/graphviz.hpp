#pragma once

#include <format>

namespace graphviz
{
        struct graph_node_atr_t {
                const char *shape     = "rectangle";
                const char *style     =   "rounded";
                const char *fixedsize =     "false";
                const char *fillcolor =   "#00b899";
        
                int   height    =    3;
                int   width     =    2;
                int   fontsize  =   30;
                int   penwidth  =    5;
                float arrowsize =  1.3f;
        };

        struct edge_t {
                int penwidth      =       5;
                const char *color = "black";
        };

        struct digraph_t {
                int dpi             =     50;
                const char *splines = "ortho";
        };

        const std::string digraph_atr_sample = "digraph {} {{                         \
                                              \ngraph [dpi = {}];                     \
                                              \nsplines = {};                         \
                                              \n";

        const std::string node_atr_sample = "\nnode{}[shape = \"{}\", style = \"{}, filled\",                    \
                                        \nheight = {}, width = {}, fixedsize = {},                               \
                                        \nfillcolor = \"{}\",                                                    \
                                        \nfontsize = {},                                                         \
                                        \npenwidth = {}                                                          \
                                        \n];\n";

        const std::string edge_atr_sample = "\nedge[penwidth = {}, color = \"{}\"];";

        const std::string node_data_key_sample  = "node{} [shape = record label = \"{{ {} | key_val: {} | parent: {} | height: {} }}\"];\n";

        const std::string nodes_tie_atr = "node{} -> node{} [color = {} arrowsize = {} penwidth = {}];\n";

        template<typename... Args>
        std::string dynamic_format(std::string_view rt_fmt_str, Args&&... args)
        {
                return std::vformat(rt_fmt_str, std::make_format_args(args...));
        }
}