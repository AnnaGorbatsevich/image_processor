add_executable(
        image_processor
        image_processor.cpp
        Parser.cpp Parser.h Filters.cpp Filters.h MatrixFilter.cpp MatrixFilter.h Reader.cpp Reader.h Writer.cpp Writer.h BMPImage.cpp BMPImage.h Controller.h Controller.cpp CropFilter.cpp CropFilter.h GsFilter.cpp GsFilter.h NegFilter.cpp NegFilter.h BlurFilter.cpp BlurFilter.h SharpFilter.cpp SharpFilter.h EdgeFilter.cpp EdgeFilter.h Exceptions.h BMP.cpp BMP.h Exception.cpp Exception.h SpheresFilter.cpp SpheresFilter.h)

add_catch(
        parser_tests
        tests/parser_tests.cpp
        Parser.cpp Parser.h Exceptions.h Exception.h Exception.cpp)

add_catch(
        controller_tests
        tests/controller_tests.cpp
        SpheresFilter.cpp Exception.h Exception.cpp Parser.h Parser.cpp Filters.cpp Filters.h MatrixFilter.cpp MatrixFilter.h Reader.cpp Reader.h Writer.cpp Writer.h BMPImage.cpp BMPImage.h Controller.h Controller.cpp CropFilter.cpp CropFilter.h GsFilter.cpp GsFilter.h NegFilter.cpp NegFilter.h BlurFilter.cpp BlurFilter.h SharpFilter.cpp SharpFilter.h EdgeFilter.cpp EdgeFilter.h Exceptions.h BMP.cpp BMP.h)


add_catch(
        crop_tests
        tests/crop_tests.cpp
        Exception.h Exception.cpp Parser.h Parser.cpp Filters.cpp Filters.h MatrixFilter.cpp MatrixFilter.h Reader.cpp Reader.h Writer.cpp Writer.h BMPImage.cpp BMPImage.h Controller.h Controller.cpp CropFilter.cpp CropFilter.h GsFilter.cpp GsFilter.h NegFilter.cpp NegFilter.h BlurFilter.cpp BlurFilter.h SharpFilter.cpp SharpFilter.h EdgeFilter.cpp EdgeFilter.h Exceptions.h BMP.cpp BMP.h SpheresFilter.cpp SpheresFilter.h)


add_catch(
        read_tests
        tests/read_tests.cpp
        Exception.h Exception.cpp Reader.cpp Reader.h BMPImage.cpp BMPImage.h Exceptions.h BMP.cpp BMP.h)

add_catch(
        write_tests
        tests/write_tests.cpp
        Exception.h Exception.cpp Writer.cpp Writer.h BMPImage.cpp BMPImage.h Exceptions.h BMP.cpp BMP.h )

add_catch(
        spheres_tests
        tests/spheres_tests.cpp
        Parser.cpp Parser.h Filters.cpp Filters.h MatrixFilter.cpp MatrixFilter.h Reader.cpp Reader.h Writer.cpp Writer.h BMPImage.cpp BMPImage.h Controller.h Controller.cpp CropFilter.cpp CropFilter.h GsFilter.cpp GsFilter.h NegFilter.cpp NegFilter.h BlurFilter.cpp BlurFilter.h SharpFilter.cpp SharpFilter.h EdgeFilter.cpp EdgeFilter.h Exceptions.h BMP.cpp BMP.h Exception.cpp Exception.h SpheresFilter.cpp SpheresFilter.h)

