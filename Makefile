include config.mk

CFLAGS += -I. -DWLR_USE_UNSTABLE -std=c99

WAYLAND_PROTOCOLS=$(shell pkg-config --variable=pkgdatadir wayland-protocols)
WAYLAND_SCANNER=$(shell pkg-config --variable=wayland_scanner wayland-scanner)

PKGS = wlroots wayland-server xcb xkbcommon libinput
CFLAGS += $(foreach p,$(PKGS),$(shell pkg-config --cflags $(p)))
LDLIBS += $(foreach p,$(PKGS),$(shell pkg-config --libs $(p)))

all: dwl

clean:
	rm -f dwl *.o *-protocol.h *-protocol.c

install: dwl
	install -Dm755 dwl $(PREFIX)/bin/dwl
	install -Dm644 dwl.1 $(MANDIR)/man1/dwl.1

uninstall:
	rm -f $(PREFIX)/bin/dwl $(MANDIR)/man1/dwl.1

.PHONY: all clean install uninstall

# wayland-scanner is a tool which generates C headers and rigging for Wayland
# protocols, which are specified in XML. wlroots requires you to rig these up
# to your build system yourself and provide them in the include path.
xdg-shell-protocol.h:
	$(WAYLAND_SCANNER) server-header \
		$(WAYLAND_PROTOCOLS)/stable/xdg-shell/xdg-shell.xml $@

xdg-shell-protocol.c:
	$(WAYLAND_SCANNER) private-code \
		$(WAYLAND_PROTOCOLS)/stable/xdg-shell/xdg-shell.xml $@

xdg-shell-protocol.o: xdg-shell-protocol.h

wlr-layer-shell-unstable-v1-protocol.h:
	$(WAYLAND_SCANNER) server-header \
		protocols/wlr-layer-shell-unstable-v1.xml $@

wlr-layer-shell-unstable-v1-protocol.c:
	$(WAYLAND_SCANNER) private-code \
		protocols/wlr-layer-shell-unstable-v1.xml $@

wlr-layer-shell-unstable-v1-protocol.o: wlr-layer-shell-unstable-v1-protocol.h

idle-protocol.h:
	$(WAYLAND_SCANNER) server-header \
		protocols/idle.xml $@

idle-protocol.c:
	$(WAYLAND_SCANNER) private-code \
		protocols/idle.xml $@

idle-protocol.o: idle-protocol.h

net-tapesoftware-dwl-wm-unstable-v1-protocol.h: protocols/net-tapesoftware-dwl-wm-unstable-v1.xml
	$(WAYLAND_SCANNER) server-header \
		protocols/net-tapesoftware-dwl-wm-unstable-v1.xml $@
net-tapesoftware-dwl-wm-unstable-v1-protocol.c: protocols/net-tapesoftware-dwl-wm-unstable-v1.xml
	$(WAYLAND_SCANNER) private-code \
		protocols/net-tapesoftware-dwl-wm-unstable-v1.xml $@
net-tapesoftware-dwl-wm-unstable-v1-protocol.o: net-tapesoftware-dwl-wm-unstable-v1-protocol.h
dwl.o: net-tapesoftware-dwl-wm-unstable-v1-protocol.h
dwl: net-tapesoftware-dwl-wm-unstable-v1-protocol.o

config.h: | config.def.h
	cp config.def.h $@

dwl.o: config.mk config.h client.h xdg-shell-protocol.h wlr-layer-shell-unstable-v1-protocol.h idle-protocol.h

dwl: xdg-shell-protocol.o wlr-layer-shell-unstable-v1-protocol.o idle-protocol.o
