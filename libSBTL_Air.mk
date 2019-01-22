#
# build libSBTL_Air using libMesh's build system
#
LIBSBTL_AIR_DIR       := $(AIR_DIR)/contrib/libSBTL_Air

LIBSBTL_AIR_srcfiles  :=
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/CP_VU_AIR.cpp
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/CV_VU_AIR.cpp
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/ETA_VU_AIR.cpp
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/G_VU_AIR.cpp
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/HS_FLASH.cpp
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/HV_FLASH.cpp
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/LAMBDA_VU_AIR.cpp
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/P_VU_AIR.cpp
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/PH_FLASH.cpp
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/PS_FLASH.cpp
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/PT_FLASH.cpp
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/S_VU_AIR.cpp
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/T_VU_AIR.cpp
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/U_VH_AIR_INI.cpp
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/U_VP_AIR.cpp
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/U_VT_AIR.cpp
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/VU_HP_AIR_INI.cpp
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/VU_AIR.cpp
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/VU_SH_AIR_INI.cpp
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/VU_SP_AIR_INI.cpp
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/VU_TP_AIR_INI.cpp
LIBSBTL_AIR_srcfiles  += $(LIBSBTL_AIR_DIR)/W_VU_AIR.cpp

LIBSBTL_AIR_objects   := $(patsubst %.cpp, %.$(obj-suffix), $(LIBSBTL_AIR_srcfiles))
LIBSBTL_AIR_deps      := $(patsubst %.$(obj-suffix), %.$(obj-suffix).d, $(LIBSBTL_AIR_objects))
LIBSBTL_AIR_LIB       := $(LIBSBTL_AIR_DIR)/libSBTL_Air-$(METHOD).la

app_INCLUDES += -I$(AIR_DIR)
app_LIBS += $(LIBSBTL_AIR_LIB)

$(LIBSBTL_AIR_LIB): $(LIBSBTL_AIR_objects)
	@echo "Linking Library "$@"..."
	@$(libmesh_LIBTOOL) --tag=CC $(LIBTOOLFLAGS) --mode=link --quiet \
	  $(libmesh_CC) $(libmesh_CFLAGS) -o $@ $(LIBSBTL_AIR_objects) $(libmesh_LDFLAGS) $(EXTERNAL_FLAGS) -rpath $(LIBSBTL_AIR_DIR)
	@$(libmesh_LIBTOOL) --mode=install --quiet install -c $(LIBSBTL_AIR_LIB) $(LIBSBTL_AIR_DIR)

$(app_EXEC): $(LIBSBTL_AIR_LIB)

-include $(LIBSBTL_AIR_deps)

cleanlibsbtl_nitrogen:
	@echo "Cleaning libSBTL_Air"
	@rm -f $(LIBSBTL_AIR_objects)
	@rm -f $(LIBSBTL_AIR_deps)
	@rm -f $(LIBSBTL_AIR_LIB)
	@rm -f $(LIBSBTL_AIR_DIR)/libSBTL_Air-$(METHOD)*.dylib
	@rm -f $(LIBSBTL_AIR_DIR)/libSBTL_Air-$(METHOD)*.so*
	@rm -f $(LIBSBTL_AIR_DIR)/libSBTL_Air-$(METHOD)*.a
