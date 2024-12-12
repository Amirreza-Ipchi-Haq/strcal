COMMITMESSAGE=""
EDIT=vi
commit:
	git add .
	if test -n "${COMMITMESSAGE}";then\
		git commit -m "${COMMITMESSAGE}";\
	else\
		git commit;\
	fi
fetch:
	git fetch
	curl https://raw.githubusercontent.com/Amirreza-Ipchi-Haq/dynastr/refs/heads/main/dynastr.h>C/dynastr.h
help:
	echo "Makefile commands:\n\tcommit [COMMITMESSAGE=<message>]  Commit to the repository using\n\t                                  <message> as the commit message (Leave\n\t                                  empty to enter description as well)\n\tfetch                             Fetch updates from the repository\n\thelp                              Show help\n\tpush                              Push updates to the repository"
push:
	git push
