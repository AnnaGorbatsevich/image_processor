add_executable(
        image_processor
        image_processor.cpp
        Parser.cpp Parser.h Filters.cpp Filters.h MatrixFilter.cpp MatrixFilter.h Reader.cpp Reader.h Writer.cpp Writer.h BMPImage.cpp BMPImage.h Controller.h Controller.cpp CropFilter.cpp CropFilter.h GsFilter.cpp GsFilter.h NegFilter.cpp NegFilter.h BlurFilter.cpp BlurFilter.h SharpFilter.cpp SharpFilter.h EdgeFilter.cpp EdgeFilter.h Exceptions.h BMP.cpp BMP.h Exception.cpp Exception.h SpheresFilter.cpp SpheresFilter.h)
