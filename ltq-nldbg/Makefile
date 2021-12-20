include $(TOPDIR)/rules.mk

PKG_NAME:=ltq-nldbg
PKG_LICENSE:=GPL-2.0-only
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/ltq-nldbg
  SECTION:=base
  CATEGORY:=Network
  TITLE:=Debug log client for Lantiq driver
endef

define Build/Configure
endef

define Build/Compile
	$(TARGET_CC) $(TARGET_CFLAGS) -o $(PKG_BUILD_DIR)/ltq-nldbg.o -c $(PKG_BUILD_DIR)/nldbg.c
	$(TARGET_CC) $(TARGET_LDFLAGS) -o $(PKG_BUILD_DIR)/$1 $(PKG_BUILD_DIR)/ltq-nldbg.o
endef

define Package/ltq-nldbg/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ltq-nldbg $(1)/usr/bin
endef
 
$(eval $(call BuildPackage,ltq-nldbg))
