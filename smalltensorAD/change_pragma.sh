files=./*

# for f in $files
# do
# 	echo "Processing $f file ..."
# 	cat $f
# done

find . -type f -name "*.h*" -exec sed -e "/ifndef/,+1d" -i {} \;
find . -type f -name "*.cu" -exec sed -e "/ifndef/,+1d" -i {} \;
find . -type f -name "*.h*" -exec sed -e "/^#endif/d" -i {} \;
find . -type f -name "*.cu" -exec sed -e "/^#endif/d" -i {} \;
find . -type f -name "*.h*" -exec sed -e "1i #pragma once" -i {} \;
find . -type f -name "*.cu" -exec sed -e "1i #pragma once" -i {} \;


find . -type f -name "*.hpp" -exec sed -e "s/Index/Ident/g" -i {} \;
find . -type f -name "*core.hpp" -exec sed -e "s/Index/Ident/g" -i {} \;
find . -type f -name "*.h" -exec sed -e "s/Index/Ident/g" -i {} \;
find . -type f -name "*.cpp" -exec sed -e "s/Index/Ident/g" -i {} \;


find . -type f -name "*.hpp" -exec sed -e "s/\._graph)/\.get_graph())/g" -i {} \;
find . -type f -name "*.h" -exec sed -e "s/\._graph)/\.get_graph())/g" -i {} \;
find . -type f -name "*.cpp" -exec sed -e "s/\._graph)/\.get_graph())/g" -i {} \;


find . -type f -name "*core.hpp" -exec sed -e "/#pragma\ once/d" -i {} \;
find . -type f -name "*core.h" -exec sed -e "/#pragma\ once/d" -i {} \;



sed -e "s/\._graph)/\.get_graph())/g" -i expr2_doubleDot.hpp

# sed -e "s/(\*(/(/g" -i expr2_doubleDot.hpp

# files=( $(find . -name "*.h*" ) )
# # deepest_dir_array=( $(find . -type d -links 3 ) )

# # for element in $(seq 0 $((${#deepest_dir_array[@]} - 1)))
# for element in $files
# do
# 	echo "Processing $element file ..."
# 	# cat $element
# done
